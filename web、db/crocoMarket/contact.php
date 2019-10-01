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

				<div class="col-lg-8 col-md-12">
					<div class="blog-posts">

						<div class="single-post">
							<div class="image-wrapper"><img src="images/jeshoots-com-219386-unsplash.jpg" alt="Blog Image"></div>

							<h3 class="title"><b class="light-color"><font face="微軟正黑體">客服專區</font></b></h3>
							<p class="desc">如果您對Croco Market有任何的建議或批評，我們非常歡迎您能來信指教，或致電客服專線：0800-080-808，手機另撥：88888-6666。我們將用心聆聽，並以最快的速度回應給您，謝謝。</p>

						</div><!-- single-post -->

						<div class="leave-comment-area">
							<h4 class="title"><b class="light-color"><font face="微軟正黑體">填寫回覆</font></b></h4>
							<div class="leave-comment">

								<form method="post" action="leavemessage.php">
									<div class="row">
										<div class="col-sm-6">
											<input class="name-input" name="name" type="text" placeholder="姓名">
										</div>
										<div class="col-sm-6">
											<input class="email-input" name="emailname" type="text" placeholder="Email">
										</div>
										<div class="col-sm-12">
											<input class="phone-input" name="phone" type="text" placeholder="電話">
										</div>
										<div class="col-sm-12">
											<input class="subject-input" name="subject" type="text" placeholder="主旨">
										</div>
										<div class="col-sm-12">
											<textarea class="message-input" rows="6" name="message" placeholder="建議內容"></textarea>
										</div>
										<div class="col-sm-12">
											<button class="btn btn-2" type="submit" name="sub" value="Send"><b>送出</b></button>
										</div>

									</div><!-- row -->
								</form>

							</div><!-- leave-comment -->

						</div><!-- comments-area -->

					</div><!-- blog-posts -->
				</div><!-- col-lg-4 -->


				<div class="col-lg-4 col-md-12">
					<div class="sidebar-area">

						<div class="sidebar-section about-author center-text">
							<div class="author-image"><img src="images/S_8121989366988.jpg" alt="Autohr Image"></div>

							<ul class="social-icons">
								<li><a href="#"><i class="fab fa-facebook-square fa-lg"></i></a></li>
								<li><a href="#"><i class="fab fa-twitter-square fa-lg"></i></a></li>
								<li><a href="#"><i class="fab fa-instagram fa-lg"></i></a></li>
<!-- 								<li><a href="#"><i class="ion-social-vimeo-outline"></i></a></li>
								<li><a href="#"><i class="ion-social-pinterest-outline"></i></a></li> -->
							</ul><!-- right-area -->

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

						<div class="sidebar-section advertisement-area">
							<h4 class="title"><b class="light-color">廣告</b></h4>
							<a class="advertisement-img" href="http://epage.mis.nsysu.edu.tw/files/13-1100-193427.php?Lang=zh-tw">
								<img src="images/advertisement.jpg" alt="Advertisement Image">
							</a>
						</div><!-- sidebar-section advertisement-area -->

					</div><!-- sidebar-area -->
				</div><!-- col-lg-4 -->

			</div><!-- row -->
		</div><!-- container -->
	</section><!-- section -->

	<?php include("./footer.php"); ?>

	<!-- SCIPTS -->
	<script src="common-js/jquery-3.1.1.min.js"></script>
	<script src="common-js/tether.min.js"></script>
	<script src="common-js/bootstrap.js"></script>
	<script src="common-js/scripts.js"></script>
</font>
</body>
</html>
