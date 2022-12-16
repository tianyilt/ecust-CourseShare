document.writeln("<link rel=\"stylesheet\" type=\"text\/css\" href=\"http://csdnimg.cn/pubnav/css/navtop_2012.css\" \/>");


document.writeln("<div class=\"nav_top_2011\">");
//2013-03-25 old var p__un = document.cookie.match(new RegExp("(^| )UserName=([^;]*)(;|$)"));
/*2013-03-25优先显示用户昵称 start*/
var p__un = document.cookie.match(new RegExp("(^| )UserNick=([^;]*)(;|$)"));
if (!p__un) p__un = document.cookie.match(new RegExp("(^| )UserName=([^;]*)(;|$)"));
/*优先显示用户昵称 end*/
if (p__un) {

	document.write('<p><em>' + decodeURIComponent(p__un[2]) + '</em><a href="http://my.csdn.net/my/notifications" class="notice_num" id="header_notice_num" target=_blank></a>我的：<a href="http://my.csdn.net/my/letter" target=_blank>收件箱<span id="header_letter_num"></span></a><a href="http://download.csdn.net/my" class="red" target=_top>资源</a><a href="http://write.blog.csdn.net/" class="red" target=_top>博客</a><a href="http://my.csdn.net" target=_top>空间</a><a href="https://passport.csdn.net/account/profile" target=_blank>设置</a>|<a href="https://passport.csdn.net/help/faq" target=_blank>帮助</a>|<a href="https://passport.csdn.net/account/logout" target="_top">退出</a></p>');
} else {
	document.write('<p><span style="color:red;">您还未登录！</span>|<a href="https://passport.csdn.net/account/login" target="_top">登录</a>|<a href="https://passport.csdn.net/account/register" target=_top>注册</a>|<a href="https://passport.csdn.net/help/faq" target="_blank">帮助</a></p>');
}
document.writeln("<ul>");
var nav_arr1 = ['首页','业界','移动','云计算','研发','论坛','博客','下载'];
var nav_arr2 = ['www.csdn.net', 'news.csdn.net', 'mobile.csdn.net','cloud.csdn.net','sd.csdn.net','bbs.csdn.net', 'blog.csdn.net', 'download.csdn.net'];
for (var i = 0; i < nav_arr1.length; i++)
{
    if ( i == 0 )
    {
        document.writeln('<li><a href="http://' + nav_arr2[i] + '/" target="_blank" style="color: red;">' + nav_arr1[i] + '</a></li>');
    }
    else
    {
        document.writeln('<li><a href="http://' + nav_arr2[i] + '/" target="_blank">' + nav_arr1[i] + '</a></li>');
    }
}
document.writeln("<li class=\"more\" ><h2 id=\"topnav_btnmore\" onclick=\"showNavMore(this)\"><a href=\"javascript:void(0);\">更多<\/a><\/h2>");
document.writeln("<div id=\"topnav_hidlist\">");
document.writeln("<iframe name='nav_frm' src='about:blank' width=92 height=178 scrolling=no frameborder=no></iframe>");
document.writeln("<\/div>");
document.writeln("<\/li>");
document.writeln("<\/ul>");
document.writeln("<\/div>");

function showNavMore(e) {
    var frm = window.frames['nav_frm'];
    var ss = '<!doctype html>';
    ss += '<html dir="ltr" lang="zh-CN">';
    ss += '<head>';
    ss += '<title>csdn</title>';
    ss += '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
    ss += '<link type="text/css" rel="Stylesheet" href="http://csdnimg.cn/pubnav/css/navtop_2012.css" />';
    ss += '<base target="_blank" />';
    ss += '</head>';
    ss += '<body class="navbody">';
    ss += '<div class="nav_top_2011">';
    ss += '<ul style="width:76px;" onclick="top.hide_nav_more()">';
    var arr1 = ['CTO俱乐部', '高校俱乐部', '培训充电', '程序员', 'ITeye', 'TUP'];
    var arr2 = ['club.csdn.net/cto', 'student.csdn.net', 'edu.csdn.net', 'www.programmer.com.cn', 'www.iteye.com', 'tup.csdn.net'];
    for (var i = 0; i < arr1.length; i++)
        ss += '<li><a href="http://' + arr2[i] + '/">' + arr1[i] + '</a></li>';
    ss += '</ul>';
    ss += '</div>';
    ss += '</body>';
    ss += '</html>';
    if (!frm.document.title) {
        frm.document.write(ss);
    }
    var hidList = document.getElementById("topnav_hidlist");
    var isshow = hidList.style.display == "block";
    hidList.style.display = isshow ? "none" : "block";
    e.className = isshow ? "" : "open";
    e.firstChild.blur();

    if (document.body.onclick == null) {
        document.body.onclick = function (event) {
            event = event || window.event;
            var target = event.target || event.srcElement;
            if (target.parentNode && target.parentNode.id == 'topnav_btnmore') {
                return;
            }
            if (target.id != 'topnav_btnmore') {
                hide_nav_more();
            }
        };
    }
}
function hide_nav_more() {
    document.getElementById("topnav_hidlist").style.display = "none";
    document.getElementById("topnav_btnmore").className = "";
}

// 关闭“新首页提示功能”

function closeTip () {
  var close = $( 'a#close' );
  var infoLayer = $( 'div#new_layer' );

  close.click( function () {
    infoLayer.fadeOut( 400 );
    return false;
  });
}

// Google code
var _gaq = _gaq || [];
_gaq.push(['_setAccount', 'UA-535605-6']);
_gaq.push(['_setDomainName', 'csdn.net']);
_gaq.push(['_trackPageview']);

(function() {
	var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
	ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
	var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
})();

function csdnShowSpaceNotify(data) {
    if (parseInt(data.n) > 0) {
        document.getElementById("header_notice_num").innerHTML = data.n;
    } else {
        document.getElementById("header_notice_num").innerHTML = 0;
    }
    if (parseInt(data.l) > 0) {
        document.getElementById("header_letter_num").innerHTML = "（" + data.l + "）";
    }
}
if (p__un) {
	(function() {
		var ca = document.createElement('script'); ca.type = 'text/javascript'; ca.async = true;
		ca.src = 'http://my.csdn.net/index.php/service/notifications/getnl?jsonpcallback=csdnShowSpaceNotify';
		var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ca, s);
	})();
}




var ua = navigator.userAgent.toLowerCase();
if(ua.match(/iPad/i)=="ipad") {
//document.write('<div id="ipad_adverting" style="position:fixed; z-index:1; left:0px; bottom:0px; width:100%; opacity:.8;"><a onclick=document.getElementById("ipad_adverting").style.display="none" style="position:absolute; top:0px; right:0px; width:4%; height:29%;display:inline-block;cursor:hand;"></a><a href="http://dingyue.programmer.com.cn/ipad.html" target="_blank"><img src="http://articles.csdn.net/uploads/allimg/120904/ipad_ad.jpg" width="100%" style="border-radius:1em 0;"/></a></div>');
}
