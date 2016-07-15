$(function(){
    $("#testData").click(function() {
        $("#id_PositionX").val("0");
        $("#id_PositionY").val("0");
        $("#id_PositionZ").val("6553.22");
        $("#id_OrientX").val("1");
        $("#id_OrientY").val("0");
        $("#id_OrientZ").val("0");
        $("#id_shipMass").val("3725");
        $("#id_fuelMass").val("1000");
        $("#id_shipEdgeLength").val("0.0025");
        $("#id_speedFirstX").val("-7.8375");
        $("#id_speedFirstY").val("0");
        $("#id_speedFirstZ").val("0");
        $("#id_maxRotationX").val("0");
        $("#id_maxRotationY").val("0");
        $("#id_maxRotationZ").val("0");
        $("#id_maxFuelUsagePerSec").val("100");
        $("#id_impulsePerFuel").val("2.61");
        $("#id_limitOverload").val("10");
        $("#id_maxTemperature").val("5274");
        $("#id_quantSizeOfSec").val("1");
        $("#id_numberOfQuants").val("6480");
        $("#id_displayPrecision").val("1");
        $("#id_Program").text("delay 5420\nengine 11\ndelay 29\nengine 0");
    });
});