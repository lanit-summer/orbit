var total_seconds = 0;
var total_milliseconds = 0;

var hours;
var minutes;
var seconds;

function start() {
	window.setInterval(function(){
		total_milliseconds += 20 * boost;
		total_seconds = Math.floor(total_milliseconds / 1000);

		hours   = Math.floor(total_seconds / 3600);
  		minutes = Math.floor((total_seconds - hours * 3600) / 60);
  		seconds = total_seconds - hours * 3600 - minutes * 60;

		document.getElementById("time_span_hour").innerHTML = hours + " H";
		document.getElementById("time_span_min").innerHTML = minutes + " M";
		document.getElementById("time_span_sec").innerHTML = seconds + " S";
	}, 20);
}