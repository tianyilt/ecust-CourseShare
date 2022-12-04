var CNick = function (selector) {
    
    if (!selector) selector = 'a.user_name';

    var un_eles = jQuery(selector);

    this.showNickname = function () {
        var uns = [];
        un_eles.each(function (idx) {
            uns.push(this.innerHTML);
        });
        var uri = 'http://api.csdn.net/service/open/nick';
        var data = 'users=' + uns.join(',') + '&callback=?';
        jQuery.getJSON(uri, data, printNickname);
    };

    window.printNickname = function (data) {
        un_eles.each(function (idx) {
            this.innerHTML = data[idx].n;
        });
    };
}
jQuery(function () {
    new CNick().showNickname();
});