$(function(){
    var $program = "";
    $(".command").click(function() {
        if (parseInt($(this).val()) < 0) {
            alert();
        }
        $program += $(this).text()  + " " + $(".command-value").val() + "\n";
        $("#id_Program").text($program);
    });
});