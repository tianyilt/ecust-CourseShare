    function RandomNum(min, max) {
        return Math.floor(Math.random() * (max - min) + min);
    }
    // 水平滚动插件
    (function ($) {
        $.fn.extend({
            Scroll: function (opt, callback) {
                //参数初始化
                if (!opt) var opt = {};
                var _btnRight = $("#" + opt.right); //Shawphy:向右按钮
                var _btnLeft = $("#" + opt.left); //Shawphy:向左按钮
                var timerID;
                var _this = this.eq(0).find("ul:first");
                var lineW = _this.find("li:first").width(), //获取列表宽度
											line = opt.line ? parseInt(opt.line, 10) : parseInt(this.width() / lineW, 10), //每次滚动的行数，默认为一屏，即父容器高度
											speed = opt.speed ? parseInt(opt.speed, 10) : 500; //卷动速度，数值越大，速度越慢（毫秒）
                timer = opt.timer //?parseInt(opt.timer,10):3000; //滚动的时间间隔（毫秒）
                if (line == 0) line = 1;
                var rightWidth = 0 - line * lineW;
                //滚动函数
                var scrollRight = function () {
                    _btnRight.unbind("click", scrollRight);
                    _this.animate({
                        marginLeft: rightWidth
                    }, speed, function () {
                        for (i = 1; i <= line; i++) {
                            _this.find("li:first").appendTo(_this);
                        }
                        _this.css({ marginLeft: 0 });
                        _btnRight.bind("click", scrollRight);
                    });

                }
                //Shawphy:向左翻页函数
                var scrollLeft = function () {
                    _btnLeft.unbind("click", scrollLeft);
                    for (i = 1; i <= line; i++) {
                        _this.find("li:last").show().prependTo(_this);
                    }
                    _this.css({ marginLeft: rightWidth });
                    _this.animate({
                        marginLeft: 0
                    }, speed, function () {
                        _btnLeft.bind("click", scrollLeft);
                    });
                }
                //Shawphy:自动播放
                var autoPlay = function () {
                    if (timer) timerID = window.setInterval(scrollRight, timer);
                };
                var autoStop = function () {
                    if (timer) window.clearInterval(timerID);
                };
                //鼠标事件绑定
                _this.hover(autoStop, autoPlay);
                autoPlay();
                var i = 0;
                var rd = RandomNum(0, 10);
                while (i++ < rd) {
                    scrollRight();
                }
                _btnRight.css("cursor", "pointer").click(scrollRight).hover(autoStop, autoPlay);
                _btnLeft.css("cursor", "pointer").click(scrollLeft).hover(autoStop, autoPlay);

            }
        })
    })(jQuery);