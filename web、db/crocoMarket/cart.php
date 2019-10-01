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
	<link href="06-cart/css/style.css" rel="stylesheet">
	<link href="02-Single-post/css/styles.css" rel="stylesheet">
	<link href="02-Single-post/css/responsive.css" rel="stylesheet">
	<link href="01-homepage/css/styles.css" rel="stylesheet">
	<link href="01-homepage/css/responsive.css" rel="stylesheet">
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css" integrity="sha384-DNOHZ68U8hZfKXOrtjWvjxusGo9WQnrNx2sqG0tfsghAvtVlRW3tvkXWZh58N9jp" crossorigin="anonymous">
	<link rel="Shortcut Icon" type="image/x-icon" href="./images/icon.png" />
	<script src="//maxcdn.bootstrapcdn.com/bootstrap/3.3.0/js/bootstrap.min.js"></script>
	<script src="//code.jquery.com/jquery-1.11.1.min.js"></script>
	<link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.4.0/css/font-awesome.min.css" rel='stylesheet' type='text/css'>

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
	width:30%;
	height:120px;
}

.wo{
	font-family: 'Noto Sans TC', sans-serif;
	font-size:30px;
}
</style>
<style>
@import url(http://fonts.googleapis.com/earlyaccess/notosanstc.css);

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
										<h2 class="wo">購物車一覽</h2>
									</header>
									<div class="container">
										<div class="row">
											<div class="col-md-10 col-md-offset-1" style="margin-left: 5%"> 
												<div class="panel panel-default panel-table">
													<div class="panel-body">
														<center><table class="table table-striped table-bordered table-list" style="text-align: center;">
															<thead >
																<tr>
																	<th style="text-align: center;">Item</th>
																	<th style="text-align: center;">Price</th>
																	<th style="text-align: center;">Quantity</th>
																	<th style="text-align: center;">Sum</th>
																	<th style="text-align: center;"><em class="fa fa-cog"></em></th>
																</tr> 
															</thead>
															<tbody>
																<?php
					                                                include('db.php');
					                                                $sum = 0;
					                                                if (isset($_SESSION['peopleId'])) {
					                                                	$sql = "SELECT * FROM cart WHERE peopleId = '".$_SESSION["peopleId"]."'";
					                                                	$re = mysqli_query($con,$sql);
						                                                $id=0;
						                                                while($row = mysqli_fetch_array($re)){
						                                                    $id = $id+1;
						                                                    $sum += $row['price']*$row['quantity'];
						                                                    if($id % 2 ==1 ){
						                                                        echo"<tr class='gradeC' >
						                                                        		
						                                                                <td width='15%'>".$row['gName']."</td>
						                                                                <td>".$row['price']."</td>
						                                                                <td>".$row['quantity']."</td>
						                                                                <td >".($row['price']*$row['quantity'])."</td>
						                                                                <td align='center' width='40%'>
																							<a href='cartMinus.php?bid=".$row['bId']."' class='btn btn-default'><em class='fas fa-minus'></em></a>
																							<a href='cartPlus.php?bid=".$row['bId']."' class='btn btn-default'><em class='fas fa-plus'></em></a>
																							<a href='cartDel.php?bid=".$row['bId']."' class='btn btn-danger'><em class='fa fa-trash'></em></a>
																						</td>
						                                                            </tr>";
						                                                    }else{
						                                                        echo"<tr class='gradeU'>
						                                                        		
						                                                                <td>".$row['gName']."</td>
						                                                                <td>".$row['price']."</td>
						                                                                <td>".$row['quantity']."</td>
						                                                                <td>".($row['price']*$row['quantity'])."</td>
						                                                                <td align='center' width='40%'>
																							<a href='cartMinus.php?bid=".$row['bId']."' class='btn btn-default'><em class='fas fa-minus'></em></a>
																							<a href='cartPlus.php?bid=".$row['bId']."' class='btn btn-default'><em class='fas fa-plus'></em></a>
																							<a href='cartDel.php?bid=".$row['bId']."' class='btn btn-danger'><em class='fa fa-trash'></em></a>
																						</td>
						                                                            </tr>";
						                                                    }
						                                                }
					                                                }
					                                               ?>
															</tbody>
														</table></center>
													</div> <!-- end body -->
													<div class="panel-footer">
														<div class="row">
															<div class="col col-xs-8">
																<ul class="pagination hidden-xs pull-right">
																	<?php
																		echo "Total Sum ：".$sum;
																	?>
																</ul>
															</div>
														</div>
														<div class="row">
															<div class="col col-xs-8">
																<ul class="pagination hidden-xs pull-right" >
																	<a class='category btn btn-default' data-toggle='modal' data-target='#myModal'>送出</a>
																</ul>
															</div>
														</div>
														<div class='modal fade' id='myModal' tabindex='-1' role='dialog' aria-labelledby='myModalLabel' aria-hidden='true'>
															<div class='modal-dialog'>
																<div class='modal-content'>
																	<?php
																	if (isset($_SESSION['peopleId'])) {
																		$sql = "SELECT bId FROM cart WHERE peopleId = '".$_SESSION["peopleId"]."'";
																        $result = mysqli_query($con,$sql);
																        $count = mysqli_num_rows($result);
																        if ($count == 0) {
																        	echo 	"<div class='modal-content'>
																						<div class='imgcontainer'>
				                                                                            <img class='myimages' src='x.gif'>
				                                                                            <div  class='word'>購物車無項目 !</div>
				                                                                     	</div>
																					</div>
																					<a class='btn btn-default' href='./shop.php'>Close</a>";
																        }else{
																        	echo 	"<div class='modal-content'>
																						<div class='imgcontainer'>
				                                                                            <img class='myimages' src='order.gif'>
				                                                                            <div  class='word'>已送出訂單 !</div>
				                                                                     	</div>
																					</div>
																					<a class='btn btn-default' href='./cartSubmit.php'>Close</a>";
																		}
																	}else{
																		echo 	"<div class='modal-content'>
																					<div class='imgcontainer'>
			                                                                            <img class='myimages' src='1.png'>
			                                                                            <div class='word'>請先登入會員</div>
																					</div>
																				<a class='btn btn-default' href='./login.php'>Close</a>";
																	}
																	?>
																	
																</div>
															</div>
														</div>
													</div> <!-- end footer -->
												</div>
											</div>
										</div>
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
	<script src="02-Single-post/js/jquery.min.js"></script>
	<!-- <script src="02-Single-post/js/jquery.poptrox.min.js"></script> -->
	<script src="02-Single-post/js/jquery.scrolly.min.js"></script>
	<script src="02-Single-post/js/skel.min.js"></script>
	<script src="02-Single-post/js/util.js"></script>
	<script src="02-Single-post/js/main.js"></script>
</body>
</html>
