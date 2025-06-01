#include "httplib.h"          // single header (third_party)
#include "csv_reader.hpp"
#include "kde.hpp"
#include "bandwidth.hpp"
#include <nlohmann/json.hpp>  // single header (third_party)
#include <fstream>
#include <mutex>

using namespace httplib;
using json = nlohmann::json;

static CsvData g_data;
static std::mutex g_mutex;

// ---------- helpers ----------
std::string grid1d_to_csv(const Grid1D& v, double xmin, double dx) {
    std::ostringstream ss;
    ss << "x,density\n";
    // for (int i = 0; i < v.size(); ++i)
        // ss << xmin + i*dx << ',' << v(i) << '\n';
    for (int i = 0; i < static_cast<int>(v.size()); ++i)
        ss << xmin + i*dx << ',' << v[i] << '\n';
    return ss.str();
}
std::string grid2d_to_csv(const Grid2D& z,
                          double xmin,double dx,double ymin,double dy)
{
    std::ostringstream ss;
    ss << "x,y,density\n";
    // for (int r=0;r<z.rows();++r)
    //     for(int c=0;c<z.cols();++c)
    for (int r=0; r < z.rows; ++r)
        for (int c = 0; c < z.cols; ++c)
            ss << xmin+c*dx << ',' << ymin+r*dy << ',' << z(r,c) << '\n';
    return ss.str();
}
// --------------------------------

int main()
{
    Server svr;
    svr.set_mount_point("/", "./web");

    // upload
    svr.Post("/csv_upload", [](const Request& req, Response& res){
        auto file = req.get_file_value("file");
        std::ofstream ofs("/tmp/upload.csv", std::ios::binary);
        ofs.write(file.content.c_str(), file.content.size());
        ofs.close();

        std::lock_guard lock(g_mutex);
        g_data = load_numeric_csv("/tmp/upload.csv", true);
        json j; j["rows"] = g_data.n_rows(); j["cols"] = g_data.headers_numeric();
        res.set_content(j.dump(), "application/json");
    });

    // kde
    svr.Post("/kde", [](const Request& req, Response& res){
        json q = json::parse(req.body);
        std::vector<int> idx = q["col_idx"].get<std::vector<int>>();
        double hmult = q.value("h_mult", 1.0);
        int dim = idx.size();

        std::lock_guard lock(g_mutex);
        if (dim==1) {
            auto& col = g_data.numeric_cols[idx[0]];
            auto h = scott_bandwidth({col})[0] * hmult;
            auto dens = kde_1d(col, h, 512);

            double xmin = *std::min_element(col.begin(), col.end());
            double xmax = *std::max_element(col.begin(), col.end());
            double dx = (xmax - xmin) / (dens.size()-1);

            res.set_content(grid1d_to_csv(dens,xmin,dx),"text/csv");
        } else if (dim==2) {
            auto& x = g_data.numeric_cols[idx[0]];
            auto& y = g_data.numeric_cols[idx[1]];
            auto hvec = scott_bandwidth({x,y});
            std::array<double,2> h{hvec[0]*hmult,hvec[1]*hmult};
            auto dens = kde_2d(x,y,h,128);

            double xmin=*std::min_element(x.begin(),x.end());
            double xmax=*std::max_element(x.begin(),x.end());
            double ymin=*std::min_element(y.begin(),y.end());
            double ymax=*std::max_element(y.begin(),y.end());
            double dx=(xmax-xmin)/127, dy=(ymax-ymin)/127;

            res.set_content(grid2d_to_csv(dens,xmin,dx,ymin,dy),"text/csv");
        } else {
            res.status = 400;
            res.set_content("dim not supported yet", "text/plain");
        }
    });

    std::cout << "http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
}
