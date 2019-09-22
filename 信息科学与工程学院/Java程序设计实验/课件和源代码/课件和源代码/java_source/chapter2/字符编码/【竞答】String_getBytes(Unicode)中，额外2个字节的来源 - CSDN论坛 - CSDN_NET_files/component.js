/*
 * 【通用组件】用于多个页面的公共组件
 *  by: zhaoxin@csdn.net
 *  2012-10-05 AM
 */
(function (window) {

    var csdn = window.csdn || { }
    csdn.comp = {};
    /*
     * 滑动门(tab)
     * param <object> 配置项:
     * {
     *     id : 元素Id  ，
     *    highlight : 当前激活状态下的样式class ，
     *    callback : 点击事件触发后回调函数
     * }
     */
    csdn.comp.tab = function (conf) {
        this.conf = conf;
        this.Dom = {};
        this.init.apply(this, []);
    };
    csdn.comp.tab.prototype = {
        init:function () {
            var id = this.conf.id;
            this.Dom.title = $("#" + id + " .tit");
            this.Dom.li = $("#" + id + " .tit li");
            this.Dom.con = $("#" + id + " .con");
            this.addEvent();
        },
        addEvent:function (){
            var that = this,
                highlight = this.conf.highlight,
                callback = this.conf.callback;
            this.Dom.title.bind("click", function (e) {
                var target = e.target, item = {}, index = 0;
                if (target.tagName == "UL") {
                    return;
                }
                that.Dom.li.each(function (i) {
                    item = that.Dom.li[i];
                    $(item).removeClass(highlight);
                    if (target !== item) {
                        that.Dom.con[i].style.display = "none";
                    } else {
                        $(item).addClass(highlight);
                        that.Dom.con[i].style.display = "block";
                        index = i;
                    }
                });
                if (typeof callback == "function") {
                    callback(index);
                }
            })
        }
    };

    /*
     * 字符数量限制
     * param <object> 配置项 :
     * {
     *   btn :  输入完成后的提交按钮
     *   textarea : 要检测字符数量的输入框
     *   tip : 输入框已输入字数文字提示
     * }
     *
     */
    csdn.comp.txtCounter = function (conf) {
        this.conf = conf;
        this.Dom = {};
        this.init.apply(this, []);
    };
    csdn.comp.txtCounter.prototype = {
        init:function () {
            this.Dom.btn = this.conf.btn;
            this.Dom.textarea = this.conf.textarea;
            this.Dom.max = this.conf.max;
            this.Dom.tip = this.conf.tip;
            this.addEvent();
        },
        addEvent:function () {
            var that = this,
                btn = this.Dom.btn,
                textarea = this.Dom.textarea,
                max = this.Dom.max,
                remain;
            this.Dom.textarea.keyup(function (e) {
                console.log(csdn.toolkit);
                var len = csdn.toolkit.computeStrLen(textarea.val())/3;
                if (len <= max) {
                    remain = parseInt(max - len);
                    that.Dom.tip.html("还可以再输入<span>" + remain + "</span>个字");
                    btn.removeClass("disabled");
                } else {
                    remain =  parseInt(len - max);
                    that.Dom.tip.html("已超出<span>" + remain + "</span>个字");
                    btn.addClass("disabled");
                }
            });
        }
    }

    /*
     * 分页
     * param <object> 配置项：
     * {
     *   size : 每分页显示实体数据数量，
     *   wrap ：实现分页组件的DOM元素，
     *   curr : 当前页号码，
     *   total : 实体数据总数量 ，
     *   shownum :  每个分页可显示页码数量
     *   callback : 点击每个页码触发的回调函数
     * }
     */
    csdn.comp.pagination = function (conf) {
        this.conf = conf;
        this.init.apply(this, []);
    };
    csdn.comp.pagination.prototype = {
        init:function (conf) {
            conf = conf || this.conf;
            this.wrap = conf.wrap || this.wrap;
            this.callback = conf.callback || this.callback;
            this.render(conf);
            this.addEvent();
        },
        render:function (conf) {
            var that = this;
            var size = this.size = conf.size || 10,
                curr = this.curr = conf.curr * 1 || 1,
                total = this.total = conf.total || 0;
            showNum = this.conf.shownum || 10;
            var totalpage = this.totalpage;
            totalpage = this.totalpage = parseInt(total / size);
            (total % size > 0) && totalpage++;
            var hlClass = conf.hlClass || "on",
                wrap = this.wrap || conf.wrap;
            //构造页码组
            var buildPages = function (start, end, pages) {
                pages = pages || [];
                if (start < len) {
                    return
                }
                var j = 1;
                start = start || "0";
                start = start * 1;
                end = end || showNum;
                end = (end > totalpage) ? totalpage : end;
                var len = (end > totalpage) ? totalpage : end;
                if (start < len) {
                    pages.push([start, end]);
                    buildPages(end, end + showNum, pages);
                }
                return pages;
            };

            //获取当前页码组
            var fetchPages = function (pages, curr) {
                for (var i = 0, len = pages.length, item; i < len; i++) {
                    item = pages[i];
                    if (curr >= item[0] && curr <= item[1]) {
                        return item;
                    }
                }
            };

            var pageList = function (curr, pages) {
                var newPageList = [], _curr;
                var i = pages[0], len = pages[1];
                while (i < len) {
                    _curr = (i == curr - 1) ? 'on' : '';
                    newPageList.push('<a class="pages ' + _curr + '" href="javascript:void(0);"  lang="' + (i * 1 + 1) + '">' + (i * 1 + 1) + '</a>');
                    i++;
                }
                return newPageList;
            };
            pageList = pageList(curr, fetchPages(buildPages(), curr));
            pageList = pageList.join("");
            var tpl = '<span style="display:none;">共<span class="num">' + total + '</span>个 </span>共<span class="total">' + totalpage + '</span>页 <a class="homepage" href="javascript:void(0);">首页</a>&nbsp;&nbsp;<a class="prev" href="javascript:void(0);">上一页</a>&nbsp;' + pageList + '&nbsp;<a class="next" href="javascript:void(0);">下一页</a>&nbsp;&nbsp;<a class="endpage" href="javascript:void(0);">末页</a>';
            wrap.html(tpl);
        },
        addEvent:function () {
            var that = this;
            $(that.wrap).bind("click", function (e) {
                that.eventHandler(that.wrap, e);
            })
        },
        eventHandler:function (wrap, e) {
            var that = this,
                target = e.target,
                hook = {
                    "pages":function () {
                        that.setPage($(target).attr("lang"));
                    },
                    "homepage":function () {
                        that.setPage(1);
                    },
                    "endpage":function () {
                        that.setPage(that.totalpage + 1);
                    },
                    "prev":function () {
                        if (that.curr > 1) {
                            that.setPage(that.curr - 1);
                        }
                    },
                    "next":function () {
                        if (that.curr < that.totalpage + 1) {
                            that.setPage(that.curr + 1);
                        }
                    }
                };
            target = $(target);
            for (var i in hook) {
                if (hook.hasOwnProperty(i) && target.hasClass(i)) {
                    hook[i]();
                }
            }
        },
        setPage:function (i) {
            this.conf.curr = i;
            this.callback(i);
        }
    }

    /*
     * 文字提示
     * param <object> 配置项
     * {
     *   el ： 要实现文字提示的DOM元素
     *   txt : <string>提示文本
     * }
     */
    csdn.comp.tip = function (el, txt) {
        if (!txt) {
            return
        }
        var tip;
        if ($(el).parent().find('.noticetip').length > 0) {
            $(el).parent().find('.noticetip').remove();
        }
        tip = $("<div class=\"noticetip\">" + txt + "</div>").insertBefore(el);
        tip[0].style.left = $(el).offset().left + 'px';
        tip[0].style.top = $(el).offset().top + 'px';
        tip.animate({
            top:'-=30'
        }, 300, function (e) {
            $(this).delay(500).animate({
                opacity:0,
                top:'-=10'
            }, 200)
        });
    };

    /*
     *   社交分享(目前可支持新浪微博，腾讯微博，qq空间，facebook,twitter,网易微博，sohu微博，人人，微信，豆瓣分享)
     *  param <object>配置项
     * {
     *   url : 分享URL,默认为当前页面URL
     *   title : 分享的文字内容(可选，默认为所在页面的title)
     *   pic : 分享图片的路径(可选)
     *   wrap : 分享按钮的DOM节点
     *   position : 分享按钮与wrap位置关系，可选为before，inline，after
     *   ralateuid : {
     *		“tsina”: “新浪用户的UID，分享微博会@该用户(可选)“，
     *		“tqq”:	”腾讯微博用户的UID，分享微博会@该用户(可选)”
     *	｝
     *   socialWebIds ：[tsina,tqq,qzone,renren,weixin,douban,twitter,fb,tsohu,t163] //缺省值为新浪微博，腾讯微博
     *   appkey : {
     *      "tsina":"您网站的新浪微博APPKEY",
            "tqq":"您网站的腾讯微博APPKEY",
           "tpeople":"您网站的人民微博APPKEY"
     *   }
     * }
     */
    csdn.comp.socialShare = function (conf) {
        var wrap = conf.wrap || document.body,
            socialWebIds = conf.socialWebIds || ['tsina','tqq'],
            pos = conf.position || 'after',
            setPos = {
                'before' : function(wrap,tpl){
                    wrap.before(tpl);
                },
                'after' : function(wrap,tpl){
                    wrap.after(tpl);
                },
                'inline' : function(wrap,tpl){
                    wrap.append(tpl);
                }
            },
            tpl = '<span id="ckepop"></span>',
            oDom = $(tpl),
            socialWebIdObj = {
                "tsina" : "tsina",
                "tqq" : "tqq",
                "qzone" : "qzone",
                "renren" : "renren",
                "weixin" : "weixin",
                "douban"  : "douban",
                "twitter" : "twitter",
                "fb" : "fb",
                "tsohu" : "tsohu",
                "t163" : "t163"
            };
        jiathis_config = {
            url : conf.url || location.href, /** 分享URL,默认为当前页面URL */
            title : conf.title || document.title, /**分享的文字内容(可选，默认为所在页面的title)*/
            pic: conf.pic || '' , /**分享图片的路径(可选)*/
            ralateuid: conf.ralateuid || '', /**关联用户的UID，分享微博会@该用户(可选)*/
            sm : socialWebIds.join(','),
            searchPic : true,
            appkey : conf.appkey,
        }
        setPos[pos]($(conf.wrap),oDom);
        $.each(socialWebIds,function(i,index){
            for( var id in socialWebIdObj){
               if( socialWebIdObj.hasOwnProperty(id) && id == index){
                    $('<a class="jiathis_button_'+ socialWebIdObj[id] + '"></a>').appendTo(oDom);
                } 
            }
            
        });  
                  
        $.getScript('http://v3.jiathis.com/code/jia.js?uid=1',function(){
            
        });
    };


    /*
     *单页面加载更多数据
     *param <object> 配置项：{
     *  wrap : 实现loadMore 功能的dom元素
     *  size : 每次点击更多加载数量
     *  curr : 当前加载次数，首次加载默认为1
     *  total : 所要加载数据的总数量
     * }
    */
    csdn.comp.loadMore = function(conf){
        this.conf = conf;
        this.init.apply(this,[]);
    };
    csdn.comp.loadMore.prototype = {
        init:function(conf){
            conf = conf || this.conf;
            this.wrap = conf.wrap || this.wrap;
            this.callback = conf.callback || this.callback;
            this.render(conf);
            this.addEvent();
        },
        render : function(conf){
            var that = this;
            var size = this.loadSize = conf.loadSize || 10,
                firstSize = this.firstSize = conf.firstSize || size,
                curr = this.curr = conf.curr * 1 || 1,
                total = this.total = conf.total || 0;
            if(curr===1){
                $('<div class="data_list"></div>').appendTo(this.wrap);
            }
            if(curr <= Math.ceil((total-firstSize)/size+1)){
                if($(".more").length==0){
                     $('<div class="more"><a href="javascript:void(0)" class="load_more">更多</a></div>').appendTo(this.wrap);
                }
                if(curr == Math.ceil((total-firstSize)/size+1)){
                    this.wrap.find(".more").remove();
                }
                this.callback(curr);
            }
        },
        addEvent : function(){
            var that = this;
            this.wrap.bind("click",function(e){
                that.eventHandler(that.wrap, e);
            });
        },
        eventHandler:function (wrap, e) {
            var that = this,
                target = e.target,
                hook = {
                    "load_more":function () {
                            that.conf.curr++;
                            that.render(that.conf);
                        }

                };

            target = $(target);
            for (var i in hook) {
                if (hook.hasOwnProperty(i) && target.hasClass(i)) {
                    hook[i]();
                }
            }
        },
    };

    /*
     * 大图轮播
     * parem <object> 配置项 ：{
     *    wrap : 实现大图轮播的DOM元素，
     *    timeout : 每帧停留时间
     *    auto : 是否自动运行
     *    duration : 帧切换时间
     * }
     */

     csdn.comp.slide = function(conf){
        $.extend(this,conf);
        this.init();

     };
     csdn.comp.slide.prototype = {
        init : function(){
            this.time = null;
            this.render();
            this.addEvent();
        },
        render : function(){
            var oLi = this.wrap.find(".slide li"),
                oDiv,
                l,
                control_area = '<a href="javascript:void(0)" class="prev"></a><a href="javascript:void(0)" class="next"></a>',
                s = '<ul>';
            if(l=oLi.length){
                this.wrap.find(".slide").width(oLi.width()*l);
                oDiv=$('<div class="slide_control"></div>').appendTo(this.wrap);
                for(var i=0;i<l;i++){
                    s += '<li><a href="javascript:void(0)">'+i+'</a></li>';
                }
                s += '</ul>';
                oDiv[0].innerHTML = s;
                oDiv.width($(".slide_control li").width()*l);
                oDiv.find("li:first").addClass("on");
                $(control_area).appendTo(this.wrap);
            }
        },
        addEvent : function(){
            var that = this;
            var n =0;
            this.wrap.bind("click",function(e){
                that.eventHandler(that.wrap,e);
            });
            that.setMove(n);
            this.wrap.bind("mouseout",function(e){
                var target = e.target
                that.auto = !0;
                var n =$(target).find(".slide_control .on a").html()*1
                that.setMove(++n);
            })

        },
        setMove : function(n){
            var that = this;
            var oLi = this.wrap.find('.slide li');
            if(this.auto){
                if(this.time){
                    clearInterval(this.time);
                }
                this.time = setInterval(function(){
                    n = (n >= oLi.length) ? 0 :
                        n<0 ? 0 : n;
                    that.slideTo(n);
                    n++;
                },this.timeout);
            }
        },
        slideTo : function(n){

            var oLi = this.wrap.find('.slide li');
            var that =this;
            if((that.auto &&n>0) || (!that.auto && n >= 0)){
                this.wrap.find('.slide').animate({'left' : -oLi.width()*n },{duration: that.duration});
            }else {
                this.wrap.find('.slide').css("left",0);
            }

            this.wrap.find('.slide_control li').removeClass('on');
            this.wrap.find('.slide_control li:eq(' + n +')').addClass('on');
        },

        eventHandler : function(wrap,e){
            var target = e.target,
                that = this,
                hook = {
                    ".slide_control li" : function(){
                        clearInterval(that.time);
                        that.auto = !1;
                        wrap.find(".slide_control li").removeClass('on');
                        $(target).parent().addClass('on');
                        that.slideTo($(target).html());
                    },
                    ".prev" :function(){
                        clearInterval(that.time);
                        that.auto = !1;
                        var n = that.wrap.find(".on a").html();
                        console.log(n)
                        that.slideTo(--n);
                    },
                    ".next" : function(){
                        clearInterval(that.time);
                        that.auto = !1;
                        var n = that.wrap.find(".on a").html()*1;
                        that.slideTo(++n);
                    }

                };
                //console.log($(target).is(".prev"));
            for(var j in hook){
                if($(target).parents().filter(j).length || $(target).is(j)){
                    //console.log(1);
                    hook[j]();
                }
            }
        }
     };

    /**
     * 返回到顶部效果
     * @description
     *     将app/csdn/returnTop/returnTo.html中的JS移动至此
     */
    csdn.scrollTop = function () {
        var topArrow = $( '<img alt="Top_arrow" id="top_arrow" src="http://csdnimg.cn/www/images/top_arrow.png" />' );
        topArrow.css( {
            display: 'none',
            cursor: 'pointer',
            border: '0 none',
            bottom: '80px',
            height: 'auto',
            margin: 0,
            opacity: 0.5,
            padding: 0,
            position: 'fixed',
            right: '40px',
            width: '35px'
        } );
        $( 'body' ).append( topArrow );

        $(window).scroll(function(){
            $( window ).scrollTop() > 20 ? $( topArrow ).fadeIn( 400 ) : $( topArrow ).fadeOut( 400 );
        });

        $('body,html').scroll(function(){
            $( 'body, html' ).scrollTop() > 20 ? $( topArrow ).fadeIn( 400 ) : $( topArrow ).fadeOut( 400 );
        });

        //当点击跳转链接后，回到页面顶部位置
        $( topArrow ).click(function(){
            $('body,html').animate({scrollTop:0},400);
            return false;
        });
    };

    /**
     * 搜索建议功能
     * @param <Object> conf
     * @deprecated conf = { search: 搜索框ID/className }
     * @author liuwei@csdn.net(瓜籽：只要再好那么一点点！)
     * @see https://github.com/devbridge/jQuery-Autocomplete
     **/
    csdn.comp.search = function ( conf ) {
        this.conf = conf;
        this.search = $( conf.search );
        this.init.apply( this, [] );
    };

    csdn.comp.search.prototype = {
        init: function () {
            this.sentData();
        },

        sentData: function () {
            var ops = {
                serviceUrl: 'http://recommend.api.csdn.net/tag/complete?X-ACL-TOKEN=tag_suggest_kdfjkqwuiplkajmncbsb_token',
                maxHeight: 'auto',
                width: 'auto',
                dataType: 'jsonp',
                onSelect: function ( data ) {
                    // Todo....
                    alert( data.value );
                }
            };
            $.extend( ops, this.conf );
            this.search.autocomplete( ops );
        }
    };

    //csdn.search = csdn.comp.search;
    window["csdn"] = csdn;
})(window);


