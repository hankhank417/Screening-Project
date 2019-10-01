<?php  
session_start();
?> 
<!DOCTYPE HTML>
<html lang="en">
<head>
	<title>CrocoMarket</title>
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
	<meta charset="UTF-8">
	<link href="https://fonts.googleapis.com/css?family=Roboto:300,400,500" rel="stylesheet">
	<link href="common-css/bootstrap.css" rel="stylesheet">
	<link href="common-css/ionicons.css" rel="stylesheet">
	<link href="common-css/layerslider.css" rel="stylesheet">
	<link href="01-homepage/css/styles.css" rel="stylesheet">
	<link href="01-homepage/css/responsive.css" rel="stylesheet">
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css" integrity="sha384-DNOHZ68U8hZfKXOrtjWvjxusGo9WQnrNx2sqG0tfsghAvtVlRW3tvkXWZh58N9jp" crossorigin="anonymous">
	<link rel="Shortcut Icon" type="image/x-icon" href="./images/icon.png" />
</head>
<body>
	<font face="微軟正黑體">

	<?php include('./header.php'); ?>

	<div class="main-slider">
		<div id="slider">
			<div class="ls-slide" data-ls="bgsize:cover; bgposition:50% 50%; duration:4000; transition2d:104; kenburnsscale:1.00;">
				<img src="images/slider-1-1600x800.png" class="ls-bg" alt="" />
					<div class="slider-content ls-l" style="top:60%; left:30%;" data-ls="offsetyin:100%; offsetxout:-50%; durationin:800; delayin:100; durationout:400; parallaxlevel:0;">
						<a class="btn" href="#">點我下載</a>
						<h3 class="title"><b>Croco Market 官方網站獨家上線!</b></h3>
						<h6>下載並了解更多優惠內容</h6>
					</div>
			</div><!-- ls-slide -->
			<div class="ls-slide" data-ls="bgsize:cover; bgposition:50% 50%; duration:4000; transition2d:104; kenburnsscale:1.00;">
				<img src="images/slider-2-1600x800.png" class="ls-bg" alt="" />
					<div class="slider-content ls-l" style="top:60%; left:30%;" data-ls="offsetyin:100%; offsetxout:-50%; durationin:800; delayin:100; durationout:400; parallaxlevel:0;">
						<a class="btn" href="./shop.php">點擊購買</a>
						<h3 class="title"><b>Croco 官方T-shirt 限時搶購中</b></h3>
						<h6>數量有限，要買要快</h6>
					</div>
			</div><!-- ls-slide -->
		</div><!-- slider -->
	</div><!-- main-slider -->
	<section class="section blog-area">
		<div class="container">
			<div class="row">
				<div class="col-lg-8 col-md-12">
					<div class="blog-posts">
						<div class="single-post">
							<div class="image-wrapper"><img src="images/christmas.jpg" alt="Blog Image"></div>
							<p class="date"><em>2018/12/23 - 2018/12/26</em></p>
							<h3 class="title"><a href="shop.php"><b class="light-color">聖誕節優惠~ 消費滿699免運費</b></a></h3>
							<p>2018大家最喜愛的節日之一聖誕節來臨啦! Croco醜鱷也來瘋聖誕！只要在活動期間(12/23~12/26)結帳金額滿699元，我們都免運費。咱們小編也在瘋聖誕了，你還不快快下手嗎?!趕快陪Croco一起穿上聖誕裝，動一動手指選購商品吧！</p>
							<a class="btn read-more-btn" href="shop.php"><b>了解更多</b></a>
						</div><!-- single-post -->
						<div class="single-post">
							<div class="image-wrapper"><img src="images/2019.jpg" alt="Blog Image"></div>
							<h6 class="date"><em>2018/12/26 - 2019/01/05</em></h6>
							<h3 class="title"><a href="shop.php"><b class="light-color">跨年優惠限時一天！滿499不僅免運，還送小驚喜包！</b></a></h3>
							<p>跨年優惠限時一天！高達40樣商品買一送一，還送驚喜小福袋！2018即將來到尾聲啦!2019的到來就讓Croco陪你放肆血拚吧，好好犒勞這一年辛苦勞作的自己！商品賣完就沒有咯，心動了還不快按下行事曆把Croco的新年活動放進備忘錄，提醒自己要行動哦</p>
							<a class="btn read-more-btn" href="shop.php"><b>了解更多</b></a>
						</div><!-- single-post -->
						<?php
							include('./db.php');
							$sql = "SELECT gName, clickCount, dir, introduce FROM imageList INNER JOIN stock ON imageList.name = stock.gName 
									ORDER BY stock.clickCount LIMIT 4";
							$result = mysqli_query($con, $sql);
							$k = 0;
							while ($row = mysqli_fetch_array($result)){
								$leastHot[$k++] = $row;
							}
						?>
						<div class="row"><br>
							<div class="col-lg-6 col-md-12">
								<div class="single-post">
									<div class="image-wrapper"><?php echo "<img src='./admin/".$leastHot[3]['dir']."' alt='Blog Image' style='max-height:200px'>"; ?></div>
									<div class="icons">
										<div class="left-area">
											<a class="btn caegory-btn" href="#"><b>79折</b></a>
										</div>
									</div>
									<h3 class="title"><a href="#"><b class="light-color" style="text-transform:uppercase;"><?php echo $leastHot[3]['gName']; ?></b></a></h3>
									<p><?php echo $leastHot[3]['introduce']; ?></p>
									<a class="btn read-more-btn" href="shop.php"><b>去逛逛</b></a>
								</div><!-- single-post -->
							</div><!-- col-sm-6 -->
							<div class="col-lg-6 col-md-12">
								<div class="single-post">
									<div class="image-wrapper"><?php echo "<img src='./admin/".$leastHot[2]['dir']."' alt='Blog Image' style='max-height:200px'>"; ?></div>
									<div class="icons">
										<div class="left-area">
											<a class="btn caegory-btn" href="#"><b>7折</b></a>
										</div>
									</div>
									<h3 class="title"><a href="#"><b class="light-color" style="text-transform:uppercase;"><?php echo $leastHot[2]['gName']; ?></b></a></h3>
									<p><?php echo $leastHot[2]['introduce']; ?></p>
									<a class="btn read-more-btn" href="shop.php"><b>去逛逛</b></a>
								</div><!-- single-post -->
							</div><!-- col-sm-6 -->
							<div class="col-lg-6 col-md-12">
								<div class="single-post">
									<div class="image-wrapper"><?php echo "<img src='./admin/".$leastHot[1]['dir']."' alt='Blog Image' style='max-height:200px'>"; ?></div>
									<div class="icons">
										<div class="left-area">
											<a class="btn caegory-btn" href="#"><b>同商品第二件五折</b></a>
										</div>
									</div>
									<h3 class="title"><a href="#"><b class="light-color" style="text-transform:uppercase;"><?php echo $leastHot[1]['gName']; ?></b></a></h3>
									<p><?php echo $leastHot[1]['introduce']; ?></p>
									<a class="btn read-more-btn" href="shop.php"><b>去逛逛</b></a>
								</div><!-- single-post -->
							</div><!-- col-sm-6 -->
							<div class="col-lg-6 col-md-12">
								<div class="single-post">
									<div class="image-wrapper"><?php echo "<img src='./admin/".$leastHot[0]['dir']."' alt='Blog Image' style='max-height:200px'>"; ?></div>
									<div class="icons">
										<div class="left-area">
											<a class="btn caegory-btn" href="#"><b>買一送一</b></a>
										</div>
									</div>
									<h3 class="title"><a href="#"><b class="light-color" style="text-transform:uppercase;"><?php echo $leastHot[0]['gName']; ?></b></a></h3>
									<p><?php echo $leastHot[0]['introduce']; ?></p>
									<a class="btn read-more-btn" href="shop.php"><b>去逛逛</b></a>
								</div><!-- single-post -->
							</div><!-- col-sm-6 -->
							<div class="col-lg-12 col-md-12">
								<div class="single-post post-style-2">
									<div class="image-wrapper width-50 left-area">
										<img src="images/blog-7-500x400.jpg" alt="Blog Image">
									</div>
									<div class="post-details width-50 right-area">
										<h3 class="title"><!-- <a href="#"> --><b class="light-color">如何準備一頓豐盛的晚餐</b><!-- </a> -->
										</h3>
										<p>晚餐是最常與宴會、娛樂或親友聚會結合的餐。西式晚餐常附以飯後甜品或水果。吃時，有時會喝酒。
										晚餐如果吃得過量，引致肥胖的機會最大，因為晚飯後人們通常不會再進行激烈的活動，有些人更會很
										快便睡覺，積聚脂肪。漢語文言文中，則以「飧」表示。中國大陸大學生的晚飯會在下午五時後開始，七時前後結束。這是因為大陸學生的午餐時間通常在中午11至12點，所以5-6點需要開始吃晚餐，之後可能會有副修和選修的科目要上課。因為晚餐時間較早，不少學生睡前有夜宵的習慣。也可能跟大學所處的城市的發展程度相關，發展度較低城市晚上活動很少，所以晚飯會比較早。</p>
										<a class="btn read-more-btn" href="https://www.abc-cooking.com.tw/products/80_83/1.htm"><b>想知道更多</b></a>
									</div><!-- post-details -->
								</div><!-- single-post -->
							</div><!-- col-sm-6 -->
						</div><!-- row -->
					</div><!-- blog-posts -->
				</div><!-- col-lg-4 -->
				<div class="col-lg-4 col-md-12">
					<div class="sidebar-area">
						<div class="sidebar-section about-author center-text">
							<div class="author-image"><img src="images/S_8121989366988.jpg" alt="Autohr Image"></div>
							<h4 class="author-name"><b class="light-color">神秘的創辦人</b></h4>
							<p>Croco Market的創辦人是神祕的<br>除非您是他的好友或家人<br>否則不管用什麼方法都找不到他</p>
							<div class="signature-image"><img src="images/signature.png" alt="Signature Image"></div>
							<a class="read-more-link" href="aboutCroco.php"><b>了解更多</b></a>
						</div><!-- sidebar-section about-author -->
						<div class="sidebar-section newsletter-area">
							<h5 class="title"><b>聯絡Croco</b></h5>
							<form action="mailto:crocomarket@gmail.com" method="POST" enctype="text/plain">
								<input class="email-input" type="text" placeholder="您的電子郵件信箱">
								<button class="btn btn-2" type="submit">送出</button>
							</form>
						</div><!-- sidebar-section newsletter-area -->
						<div class="sidebar-section category-area">
							<h4 class="title"><b class="light-color">商品類別</b></h4>
							<a class="category" href="shop.php">
								<img src="images/category-1-400x150.jpg" alt="Category Image">
								<h6 class="name">食品</h6>
							</a>

							<a class="category" href="javascript:alert('Opps 頁面開發中...')">
								<img src="images/category-2-400x150.jpg" alt="Category Image">
								<h6 class="name">居家</h6>
							</a>

							<a class="category" href="javascript:alert('Opps 頁面開發中...')">
								<img src="images/category-3-400x150.jpg" alt="Category Image">
								<h6 class="name">服裝</h6>
							</a>
							<a class="category" href="javascript:alert('Opps 頁面開發中...')">
								<img src="images/category-4-400x150.jpg" alt="Category Image">
								<h6 class="name">3C</h6>
							</a>
						</div><!-- sidebar-section category-area -->
						<div class="sidebar-section latest-post-area">
							<h4 class="title"><b class="light-color">Croco 知識+</b></h4>
							<div class="latest-post" href="#">
								<div class="l-post-image"><img src="images/recent-post-1-150x200.jpg" alt="Category Image"></div>
								<div class="post-info">
									<a class="btn category-btn" href="http://news.ltn.com.tw/news/business/paper/1177971">閱讀全文</a>
									<h5><a href="http://news.ltn.com.tw/news/business/paper/1177971"><b class="light-color">AI機器人 今年可望進駐賣場</b></a></h5>
									<h6 class="date"><em>2018/02/21</em></h6>
								</div>
							</div>
							<div class="latest-post" href="#">
								<div class="l-post-image"><img src="images/recent-post-2-150x200.png" alt="Category Image"></div>
								<div class="post-info">
									<a class="btn category-btn" href="https://www.cw.com.tw/article/article.action?id=5090389">閱讀全文</a>
									<h5><a href="https://www.cw.com.tw/article/article.action?id=5090389"><b class="light-color">為何柳丁要用紅色網袋裝？</b></a></h5>
									<h6 class="date"><em>2018/06/08</em></h6>
								</div>
							</div>
							<div class="latest-post" href="#">
								<div class="l-post-image"><img src="images/recent-post-3-150x200.jpg" alt="Category Image"></div>
								<div class="post-info">
									<a class="btn category-btn" href="https://health.udn.com/health/story/10561/3165053">閱讀全文</a>
									<h5><a href="https://health.udn.com/health/story/10561/3165053"><b class="light-color">逛賣場能治便秘?</b></a></h5>
									<h6 class="date"><em>2018/05/27</em></h6>
								</div>
							</div>
							<div class="latest-post" href="#">
								<div class="l-post-image"><img src="images/recent-post-4-150x200.jpg" alt="Category Image"></div>
								<div class="post-info">
									<a class="btn category-btn" href="https://tw.news.yahoo.com/%E8%B3%A3%E5%A0%B4%E6%B0%B4%E7%94%A2-%E9%83%BD%E6%98%AF%E5%86%B0-%E9%80%80%E5%86%B0%E5%89%A9%E5%AE%B9%E9%87%8F3%E6%88%90-145014915.html">閱讀全文</a>
									<h5><a href="https://tw.news.yahoo.com/%E8%B3%A3%E5%A0%B4%E6%B0%B4%E7%94%A2-%E9%83%BD%E6%98%AF%E5%86%B0-%E9%80%80%E5%86%B0%E5%89%A9%E5%AE%B9%E9%87%8F3%E6%88%90-145014915.html"><b class="light-color">賣場水產都是冰 退冰剩容量3成</b></a></h5>
									<h6 class="date"><em>2018/05/31</em></h6>
								</div>
							</div>
						</div><!-- sidebar-section latest-post-area -->
						<div class="sidebar-section advertisement-area">
							<h4 class="title"><b class="light-color">廣告</b></h4>
							<a class="advertisement-img" href="http://epage.mis.nsysu.edu.tw/files/13-1100-193427.php?Lang=zh-tw">
								<img src="images/advertisement.jpg" alt="Advertisement Image">
							</a>
						</div><!-- sidebar-section advertisement-area -->
					</div><!-- about-author -->
				</div><!-- col-lg-4 -->
			</div><!-- row -->
		</div><!-- container -->
	</section><!-- section -->

	<?php include("./footer.php"); ?>

	<!-- SCIPTS -->
	<script src="common-js/jquery-3.1.1.min.js"></script>
	<script src="common-js/tether.min.js"></script>
	<script src="common-js/bootstrap.js"></script>
	<script src="common-js/layerslider.js"></script>
	<script src="common-js/scripts.js"></script>
</font>
</body>
</html>
