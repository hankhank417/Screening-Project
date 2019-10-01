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
	<link href="02-Single-post/css/styles.css" rel="stylesheet">
	<link href="02-Single-post/css/responsive.css" rel="stylesheet">
	<link href="01-homepage/css/styles.css" rel="stylesheet">
	<link href="01-homepage/css/responsive.css" rel="stylesheet">
	<link rel="stylesheet"
          href="https://fonts.googleapis.com/css?family=Tangerine">
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css" integrity="sha384-DNOHZ68U8hZfKXOrtjWvjxusGo9WQnrNx2sqG0tfsghAvtVlRW3tvkXWZh58N9jp" crossorigin="anonymous">
	<link rel="Shortcut Icon" type="image/x-icon" href="./images/icon.png" />
</head>
<style>
@import url(http://fonts.googleapis.com/earlyaccess/notosanstc.css);
.imgcontainer {
    text-align: center;
    margin: 24px 0 12px 0;
    position: relative;
}
.avatar {
    width: 200px;
	height:200px;
    border-radius: 50%;
}
.word{
    width: 300px;
	height:100px;
	text-align:center;
	line-height:100px;
	margin:0 auto;
	font-size:35px;
	font-family: "Microsoft YaHei";
	color:#666666;
}

.myimages{
	width:300px;
	height:100px;
}

.wo{
	font-family: 'Noto Sans TC', sans-serif;
	font-size:30px;
}
</style>
<body>

	<?php include('./header.php'); ?>

	<section class="blog-area">
		<div class="container">
			<div class="row">
				<div class="col-lg-12 col-md-12">
					<div class="blog-posts">
						<div class="sidebar-section category-area">
							<section id="galleries">
								<div class="gallery">
									<header>
										<h2 class="wo">商品一覽</h2>
										<ul class="tabs">
											<?php
												include('./admin/db.php');
												$query = "SELECT goodFullName FROM `stock` GROUP BY goodFullName";
												$result = mysqli_query($con, $query);
					                            if (!$result) {
					                                printf("Error: %s\n", mysqli_error($con));
					                                exit();
					                            }
					                            echo "<li><a href='shop.php' class='button'>All</a></li>";
					                            while ($row = mysqli_fetch_array($result)){
		                                            echo "<li><a href='shop.php?type=".$row['goodFullName']."' class='button' style='text-transform:uppercase;'>".$row['goodFullName']."</a></li>";
					                            }
											?>
										</ul>
									</header>

									<div class="content">
										<?php
											include('./admin/db.php');
											if (!isset($_GET['type'])) {
												$query = "SELECT name, dir, goodFullName, quantity, price, id
													  	  FROM imageList INNER JOIN stock ON imageList.name = stock.gName";
											}else{
												$query = "SELECT name, dir, goodFullName, quantity, price, id
													  	  FROM imageList INNER JOIN stock ON imageList.name = stock.gName 
													  	  WHERE stock.goodFullName='".$_GET['type']."'";
											}
											
											$result = mysqli_query($con, $query);
				                            if (!$result) {
				                                printf("Error: %s\n", mysqli_error($con));
				                                exit();
				                            }
				                            $label;
				                            while ($row = mysqli_fetch_array($result)){
												echo   "<div class='media all ".$row['goodFullName']."'>
															<a class='category' data-toggle='modal' data-target='#myModal".$row['id']."'>
																<div>
																	<img src='./admin/".$row['dir']."' title = '".$row['name']."'>
																	<h6 class='name' style='text-transform:uppercase;'>".
																		$row['name'].
																		"<br>價格 : ".$row['price']."/斤".
																		", 剩餘 : ".$row['quantity'].
																	"</h6>
																</div>
															</a>
														</div>";
												if (isset($_SESSION['peopleId'])) {
													echo 	"<div class='modal fade' id='myModal".$row['id']."' tabindex='-1' role='dialog' aria-labelledby='myModalLabel' aria-hidden='true'>
															<div class='modal-dialog'>
                                                                 <div class='modal-content'>
                                                                     <div class='imgcontainer'>
                                                                               <img class='myimages' src='2.gif'>
                                                                               <div  class='word'>加入購物車成功 !</div>
                                                                     </div>
                                                                     <a class='btn btn-primary' href='./buy.php?id=".$row['id']."'>Close</a>
									                             </div>
                                                             </div>
														</div>";
												}else{
													echo 	"<div class='modal fade' id='myModal".$row['id']."' tabindex='-1' role='dialog' aria-labelledby='myModalLabel' aria-hidden='true'>
															<div class='modal-dialog'>
																<div class='modal-content'>
																	 <div class='imgcontainer'>

                                                                               <img src='1.png' alt='Avatar' class='avatar'>
                                                                               <div  class='word'>請先登入會員 !</div>
                                                                     </div>
																	<a class='btn btn-default' href='./login.php'>Close</a>
																</div>
															</div>
														</div>";
												}
				                            }
										?>
									</div>
															
								</div>
							</section>
						</div><!-- sidebar-section category-area -->
					</div><!-- blog-posts -->
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
</body>
</html>
