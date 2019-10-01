var page = require('webpage').create();
page.open('http://localhost/crocoMarket/admin/printTradeNew.php?id=2', function() {
    setTimeout(function() {
        page.render('google.png');
        phantom.exit();
    }, 200);
});