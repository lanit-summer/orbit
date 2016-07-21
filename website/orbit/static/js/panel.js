$(function() {
    $(".panel-btn").click(function() {
        var panelWidth = $(".panel").width() + "px";
        if ($(".panel-btn").css("left") == "0px") {
            $(".panel-btn").animate({left: panelWidth}, 500);
            $(".panel").animate({left: 0}, 500);
            $(".panel-btn img").attr("src", "/static/img/icons/icon5.png");
        }
        else {
            $(".panel-btn").animate({left: 0}, 500);
            $(".panel").animate({left: "-" + panelWidth}, 500);
            $(".panel-btn img").attr("src", "/static/img/icons/icon4.png");
        }
    });
    $(".controls img").click(function() {
        $(this).animate({marginBottom: "5px"}, 80);
        $(this).animate({marginBottom: "10px"}, 80);
    });
    $(".sun-modes img").click(function() {
        if ($(this).attr("src") == "/static/img/icons/icon12.png") {
            $(this).attr("src", "/static/img/icons/icon13.png");
            // turnOn();
        }
        else {
            $(this).attr("src", "/static/img/icons/icon12.png");
            // turnOff();
        }
    });
});

