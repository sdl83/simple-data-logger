var timeout=null;  //timeroutfunction
var vlSpec ={
 "$schema": "https://vega.github.io/schema/vega-lite/v2.json",
 "data": { "name": "table","format": {
      "parse": {
        "date": "utc:'%Q'"
      }
    }
   },
 "width": 1000,
  "height":500,
  "mark": "line",
  "encoding": {
    "x": {
      "timeUnit":"utcyearmonthdatehoursminutessecondsmilliseconds",
      "field": "date",
      "type": "temporal"
    },
    "y": {
      "field": "value",
      "type": "quantitative"
    }
  }
  };


  function reRender(res,newEntries){
     console.log('Starting to (re)render the visualization');
     var changeSet = vega.changeset().insert(newEntries); // generate change-set
     newEntries.length=0; //empty array
     res.view.change('table', changeSet).run(); // re-render graphic
     timeout=null; // set pointer to time out function to 0
  }
  vegaEmbed("#vis", vlSpec).then(function(res) {// create graphic
    var socket = io(); //connect to websocket server
    var newEntries=[];
    socket.on('new-line', function(line) { // on new data lines
      if(timeout!=null){  //halt current render process
       clearTimeout(timeout);
     }
       var newEntry= {'date':line.split(',')[0],'value':line.split(',')[1]};
       newEntries.push(newEntry); // add new data entry
       timeout = setTimeout(reRender, 100,res,newEntries); // launch new data render
    });
  });
