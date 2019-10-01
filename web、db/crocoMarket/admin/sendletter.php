<?php  
session_start();  
if(!isset($_SESSION["user"]))
{
 header("location:index.php");
}
?> 
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Administrator</title>
    <link href="assets/css/bootstrap.css" rel="stylesheet" />
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css" integrity="sha384-DNOHZ68U8hZfKXOrtjWvjxusGo9WQnrNx2sqG0tfsghAvtVlRW3tvkXWZh58N9jp" crossorigin="anonymous">
    <link href="assets/js/morris/morris-0.4.3.min.css" rel="stylesheet" />
    <link href="assets/css/custom-styles.css" rel="stylesheet" />
    <link href='http://fonts.googleapis.com/css?family=Open+Sans' rel='stylesheet' type='text/css' />
    <link rel="Shortcut Icon" type="image/x-icon" href="./assets/img/icon.png" />
</head>

<body>
    <div id="wrapper">
        <nav class="navbar navbar-default top-navbar" role="navigation">
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".sidebar-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="home.php"><?php echo $_SESSION["user"]; ?> </a>
            </div>

            <ul class="nav navbar-top-links navbar-right">
                <li class="dropdown">
                    <a class="dropdown-toggle" data-toggle="dropdown" href="#" aria-expanded="false">
                        <i class="fa fa-user fa-fw"></i><i class="fa fa-caret-down"></i>
                    </a>
                    <ul class="dropdown-menu dropdown-user">
                        <li><a href="usersetting.php"><i class="fa fa-user fa-fw"></i> User Profile</a></li>
                        <li class="divider"></li>
                        <li><a href="logout.php"><i class="fa fa-sign-out fa-fw"></i> Logout</a></li>
                    </ul>
                </li>
            </ul>
        </nav>

        <nav class="navbar-default navbar-side" role="navigation">
            <div class="sidebar-collapse">
                <ul class="nav" id="main-menu">
                    <li><a href="home.php"><i class="fa fa-home fa-lg"></i>Home</a></li>
                    <li><a href="stock.php"><i class="fas fa-warehouse fa-lg"></i>Stocks list</a></li>
                    <li><a href="purchaseorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Purchase Form</a></li>
                    <li><a href="returnorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Return Form</a></li>
                    <li><a href="tradepayment.php"><i class="fas fa-list-ul fa-2x"></i>Records</a></li>
                    <li><a href="profitChart.php"><i class="far fa-chart-bar fa-2x"></i>Profit Chart</a></li>
                    <li><a class="active-menu" href="sendletter.php"><i class="far fa-envelope fa-2x"></i>Send Letter</a></li>
                    <li><a href="Bill.php"><i class="fas fa-qrcode fa-2x"></i>Bill</a></li>
                </ul>
            </div>
        </nav>
        <!-- /. NAV SIDE  -->
        <div id="page-wrapper" >
            <div id="page-inner">
			 <div class="row">
                    <div class="col-md-12">
                        <h1 class="page-header">
                           News letters<small> panel</small>
                        </h1>
                    </div>
                </div> 
                 <!-- /. ROW  -->
				 
				 <div class="row">
                <div class="col-md-12">
                    <div class="jumbotron">
                        <h3>Send The News Letters to Followers</h3>
						
                        <p></p>
                        <p>
						<div class="panel-body">
                            <button class="btn btn-primary btn" data-toggle="modal" data-target="#myModal">
                              Send New News Letters
                            </button>
                            <div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                                <div class="modal-dialog">
                                    <div class="modal-content">
                                        <div class="modal-header">
                                            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                                            <h4 class="modal-title" id="myModalLabel">Compose News Letter</h4>
                                        </div>
										<form method="post" action="sendmessage.php">
										<div class="modal-body">
                                            <div class="form-group">
                                            <label>Title</label>
                                            <input name="subject" class="form-control" placeholder="Enter Title">
											</div>
                                        </div>
										<div class="modal-body">
										<div class="form-group">
										  <label for="comment">News</label>
										  <textarea name="news" class="form-control" rows="5" id="comment"></textarea>
										</div>
										 </div>
                                        <div class="modal-footer">
                                            <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
											
                                           <input type="submit" name="log" value="Send" class="btn btn-primary">
										  </form>
										   
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <?php
                        include('db.php');
                        $mail = "SELECT * FROM `contact`";
                        $rew = mysqli_query($con,$mail);
                       ?>
                        </p>
						
                    </div>
                </div>
            </div>
               <?php
				
				$sql = "SELECT * FROM `contact`";
				$re = mysqli_query($con,$sql);
				
			   ?>
            <div class="row">
                <div class="col-md-12">
                    <!-- Advanced Tables -->
                    <div class="panel panel-default">
                        <div class="panel-body">
                            <div class="table-responsive">
                                <table class="table table-striped table-bordered table-hover" id="dataTables-example">
                                    <thead>
                                        <tr>
                                            <th>Name</th>
											<th>Phone Number</th>
                                            <th>Email</th>
                                            <th>Date</th>
											<th>Status</th>
											<th>Approval</th>
											<th>Remove</th>
                                            
                                        </tr>
                                    </thead>
                                    <tbody>
                                        
									<?php
										while($row = mysqli_fetch_array($re))
										{
										
											$id = $row['id'];
											
											if($id % 2 ==1 )
											{
												echo"<tr class='gradeC'>
													<td>".$row['fullname']."</td>
													<td>".$row['phoneno']."</td>
													<td>".$row['email']."</td>
													<td>".$row['cdate']."</td>
													<td>".$row['approval']."</td>
													<td><a href=newsletter.php?eid=".$id ." <button class='btn btn-primary'> <i class='fa fa-edit' ></i> Permission</button></td>
													<td><a href=newsletterdel.php?eid=".$id ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
												</tr>";
											}
											else
											{
												echo"<tr class='gradeU'>
													<td>".$row['fullname']."</td>
													<td>".$row['phoneno']."</td>
													<td>".$row['email']."</td>
													<td>".$row['cdate']."</td>
													<td>".$row['approval']."</td>
													<td><a href=newsletter.php?eid=".$id." <button class='btn btn-primary'> <i class='fa fa-edit' ></i> Permission</button></td>
													<td><a href=newsletterdel.php?eid=".$id ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete </button></td>		
												</tr>";
											
											}
										
										}
										
									?>
                                        
                                    </tbody>
                                </table>
                            </div>
                            
                        </div>
                    </div>
                    <!--End Advanced Tables -->
                </div>
            </div>
                <!-- /. ROW  -->
            
                </div>
               
            </div>
        
               
    </div>
             <!-- /. PAGE INNER  -->
            </div>
         <!-- /. PAGE WRAPPER  -->
     <!-- /. WRAPPER  -->
    <!-- JS Scripts-->
    <!-- jQuery Js -->
    <script src="assets/js/jquery-1.10.2.js"></script>
      <!-- Bootstrap Js -->
    <script src="assets/js/bootstrap.min.js"></script>
    <!-- Metis Menu Js -->
    <script src="assets/js/jquery.metisMenu.js"></script>
     <!-- DATA TABLE SCRIPTS -->
    <script src="assets/js/dataTables/jquery.dataTables.js"></script>
    <script src="assets/js/dataTables/dataTables.bootstrap.js"></script>
        <script>
            $(document).ready(function () {
                $('#dataTables-example').dataTable();
            });
    </script>
         <!-- Custom Js -->
    <script src="assets/js/custom-scripts.js"></script>
    
   
</body>
</html>
