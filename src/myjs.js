var GetLat = function() {

  navigator.geolocation.getCurrentPosition(findMe);
  function findMe(pos) {
  var lat = pos.coords.latitude;
  var lat = String(lat);
  var sum = 0;
  var c = ''
  for(i=0; i < lat.length; i++){
    c = lat.charAt(i);
    if(c >= '0' && c <= '9'){
      sum += parseInt(c);
    }
  }
  var dict = {"KEY_SUM" : sum};
  Pebble.sendAppMessage(dict);
  }
};

Pebble.addEventListener("ready",
  function(e) {
    //App is ready to receive JS messages
    GetLat();
  }
);