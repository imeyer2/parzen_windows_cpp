let columns = [];
document.getElementById("csvFile").addEventListener("change", e=>{
  const fd=new FormData();
  fd.append("file", e.target.files[0]);
  fetch("/csv_upload",{method:"POST",body:fd})
    .then(r=>r.json()).then(j=>{
      columns=j.cols;
      const div=document.getElementById("cols");
      div.innerHTML="";
      columns.forEach((c,i)=>{
        div.innerHTML+=`<label><input type="checkbox" value="${i}"/>${c}</label> `;
      });
    });
});

document.getElementById("runBtn").addEventListener("click", ()=>{
  const idx=[...document.querySelectorAll('#cols input:checked')].map(x=>+x.value);
  if(idx.length<1||idx.length>2){alert("select 1 or 2 numeric columns");return;}
  const hMult=parseFloat(document.getElementById("hRange").value);
  fetch("/kde",{method:"POST",
      headers:{'Content-Type':'application/json'},
      body:JSON.stringify({col_idx:idx,h_mult:hMult})})
  .then(r=>r.text()).then(csv=>{
      document.getElementById("dl").style.display="inline";
      document.getElementById("dl").href=URL.createObjectURL(new Blob([csv],{type:"text/csv"}));

      const rows=csv.trim().split("\n").slice(1).map(r=>r.split(",").map(Number));
      if(idx.length===1){
        const xs=rows.map(r=>r[0]), ys=rows.map(r=>r[1]);
        Plotly.newPlot("plot",[{
          x:xs, y:ys, mode:'lines'
        }],{title:"1‑D KDE"});
      }else{
        const xs=[...new Set(rows.map(r=>r[0]))];
        const ys=[...new Set(rows.map(r=>r[1]))];
        const z=Array(ys.length).fill().map(()=>Array(xs.length).fill(0));
        rows.forEach(r=>{
          const xi=xs.indexOf(r[0]), yi=ys.indexOf(r[1]);
          z[yi][xi]=r[2];
        });
        Plotly.newPlot("plot",[{
          x:xs,y:ys,z:z,type:'surface'
        }],{title:"2‑D KDE"});
      }
  });
});
