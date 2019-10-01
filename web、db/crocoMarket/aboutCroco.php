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
	<link href="04-Contact/css/styles.css" rel="stylesheet">
	<link href="04-Contact/css/responsive.css" rel="stylesheet">
	<link href="01-homepage/css/styles.css" rel="stylesheet">
	<link href="01-homepage/css/responsive.css" rel="stylesheet">
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css" integrity="sha384-DNOHZ68U8hZfKXOrtjWvjxusGo9WQnrNx2sqG0tfsghAvtVlRW3tvkXWZh58N9jp" crossorigin="anonymous">
	<link rel="Shortcut Icon" type="image/x-icon" href="./images/icon.png" />
</head>
<body>
	<font face="微軟正黑體">

	<?php include('./header.php'); ?>

	<section class="blog-area">
		<div class="container">
			<div class="row">
				<div class="col-lg-7 col-md-11 panel panel-default" style="margin-left: auto; margin-right: auto; ">
					<div class="col-md-offset-2">
						<div class="blog-posts">
							<div class="single-post">
								<h3 class="title"><b class="light-color">保護動物 人人有責</b></h3>
								<p class="desc">鱷魚是一個很常見的動物，但是其實鱷魚也逐漸面臨絕種了嗎？大家都會認真看待其他將瀕臨絕種的動物，但是我們不能忽視現在覺得沒有危機的動物。此外，我們Croro Market 也會把每個月盈利的2%捐給鱷魚保護協會，來表示我們的一份心意。</p>
								<br><div class="image-wrapper"><img src="images/icon.png" alt="Blog Image"></div><br>
								<h3 class="title"><b class="light-color">勤勤懇懇 為了弱勢的農民們有多一條出路</b></h3>
								<p class="desc">
									我們Croco Market的主旨的為了幫助處於弱勢的農、漁、畜業者銷售出他們辛苦收穫的食品。讓大家看到這裡有一群需要幫助的業者。<br><br>
									若有善心人士想要捐款，可以聯絡我們或者前往鱷魚保護協會。
								</p><br><br>
							</div><!-- single-post -->
						</div>
					</div>
				</div>
			</div>
		</div>
	</section>

	<?php include("./footer.php"); ?>

	<!-- SCIPTS -->
	<script src="common-js/jquery-3.1.1.min.js"></script>
	<script src="common-js/tether.min.js"></script>
	<script src="common-js/bootstrap.js"></script>
	<script src="common-js/scripts.js"></script>
</font>
</body>
</html>
