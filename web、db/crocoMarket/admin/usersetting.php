<?php  
session_start();
if(!isset($_SESSION["user"]))
{
 header("location:index.php");
}

ob_start();
?> 
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
      <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>SUNRISE HOTEL</title>
	<!-- Bootstrap Styles-->
    <link href="assets/css/bootstrap.css" rel="stylesheet" />
     <!-- FontAwesome Styles-->
    <link href="assets/css/font-awesome.css" rel="stylesheet" />
        <!-- Custom Styles-->
    <link href="assets/css/custom-styles.css" rel="stylesheet" />
     <!-- Google Fonts-->
   <link href='http://fonts.googleapis.com/css?family=Open+Sans' rel='stylesheet' type='text/css' />
    <link href="assets/js/dataTables/dataTables.bootstrap.css" rel="stylesheet" />
    <link rel="Shortcut Icon" type="image/x-icon" href="./assets/img/icon.png" />

    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css" integrity="sha384-DNOHZ68U8hZfKXOrtjWvjxusGo9WQnrNx2sqG0tfsghAvtVlRW3tvkXWZh58N9jp" crossorigin="anonymous">
    <link href="assets/js/morris/morris-0.4.3.min.css" rel="stylesheet" />
    
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
                <a class="navbar-brand" href="home.php">MAIN MENU </a>
            </div>

            <ul class="nav navbar-top-links navbar-right">
                <li class="dropdown">
                    <a class="dropdown-toggle" data-toggle="dropdown" href="#" aria-expanded="false">
                        <i class="fa fa-user fa-fw"></i> <i class="fa fa-caret-down"></i>
                    </a>
                    <ul class="dropdown-menu dropdown-user">
                        <li><a href="usersetting.php"><i class="fa fa-user fa-fw"></i> User Profile</a></li>
                        <li class="divider"></li>
                        <li><a href="logout.php"><i class="fas fa-sign-out-alt"></i> Logout</a></li>
                    </ul>
                    <!-- /.dropdown-user -->
                </li>
                <!-- /.dropdown -->
            </ul>
        </nav>
        <!--/. NAV TOP  -->
        <nav class="navbar-default navbar-side" role="navigation">
            <div class="sidebar-collapse">
                <ul class="nav" id="main-menu">
                    <li><a class="active-menu" href="home.php"><i class="fa fa-home fa-lg"></i>Home</a></li>
                </ul>
            </div>
        </nav>
        <!-- /. NAV SIDE  -->
       
        <div id="page-wrapper" >
            <div id="page-inner">
    			<div class="row">
                    <div class="col-md-12">
                        <h1 class="page-header">
                           ADMINISTRATOR<small> accounts </small>
                        </h1>
                    </div>
                </div> 
                     
                                     
                <?php
    				include ('db.php');
    				$sql = "SELECT * FROM `employee` ORDER BY eId";
    				$re = mysqli_query($con,$sql)
    			?>
                    
                <div class="row">
                    <div class="col-md-12">
                        <!-- Advanced Tables -->
                        <div class="panel panel-default">
                            <div class="panel-body">
                                <div class="table-responsive">
                                    <table class="table table-striped table-bordered table-hover" id="dataTable-example">
                                        <thead>
                                            <tr>
    											<th>Name</th>
                                                <th>Sex</th>
                                                <th>Account</th>
    											<th>Password</th>
    											<th>Email</th>
    											<th>Update</th>
                                                <th>Remove</th>
                                            </tr>
                                        </thead>
                                        <tbody>
                                            
    									<?php
    										while($row = mysqli_fetch_array($re)){
    										    $id = $row['id'];
    											$name = $row['eName'];
    											$account = $row['eAccount'];
    											$password = $row['ePassword'];
    											$email = $row['eEmail'];
                                                if ($row['eSex']==1) {
                                                    $sex = "male";
                                                }else{
                                                    $sex = "female";
                                                }

    											if($id % 2 ==0 ){
    												echo"<tr class='gradeC'>
        													<td>".$name."</td>
        													<td>".$sex."</td>
        													<td>".$account."</td>
        													<td>".$password."</td>
        													<td>".$email."</td>
        													<td><a href=usersettingup.php?id=".$row['id'] ." <button class='btn btn-primary btn'>Update</button></td>
        													<td><a href=usersettingdel.php?id=".$id ."><button class='btn btn-danger'><i class='fa fa-edit' ></i> Delete</button></a></td>
    												    </tr>";
    											}
    											else{
    												echo"<tr class='gradeC'>
                                                            <td>".$name."</td>
                                                            <td>".$sex."</td>
                                                            <td>".$account."</td>
                                                            <td>".$password."</td>
                                                            <td>".$email."</td>
                                                            <td><a href=usersettingup.php?id=".$row['id'] ." <button class='btn btn-primary btn'>Update</button></td>
                                                            <td><a href=usersettingdel.php?id=".$id ."><button class='btn btn-danger'><i class='fa fa-edit' ></i> Delete</button></a></td>
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
    					<div class="panel-body">
                            <button class="btn btn-primary btn" data-toggle="modal" data-target="#myModal1">Add New Admin</button>
                            <div class="modal fade" id="myModal1" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                                <div class="modal-dialog">
                                    <div class="modal-content">
                                        <div class="modal-header">
                                            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                                            <h4 class="modal-title" id="myModalLabel">Add New Admin</h4>
                                        </div>
    									<form method="post">
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Name</label>
                                                <input name="newName"  class="form-control" placeholder="Enter User name">
                                                </div>
                                            </div>
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Sex  (0 = female, 1 = male)</label>
                                                <input name="newSex"  class="form-control" placeholder="Enter User Sex">
                                                </div>
                                            </div>
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Account</label>
                                                <input name="newAccount"  class="form-control" placeholder="Enter User name">
    											</div>
    										</div>
    										<div class="modal-body">
                                                <div class="form-group">
                                                <label>Password</label>
                                                <input name="newPassword"  class="form-control" placeholder="Enter Password">
    											</div>
                                            </div>
                                            <div class="modal-footer">
                                                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                                                <input type="submit" name="in" value="Add" class="btn btn-primary">
                                            </div>
    									</form>
                                    </div>
                                </div>
                            </div>
                        </div>
    					<?php
    					if(isset($_POST['in'])){
                            $sql ="SELECT COUNT(eId) as count FROM employee";
                            $result = mysqli_query($con, $sql);
                            $row = mysqli_fetch_array($result);
                            $count = $row['count'];
                            $newName = $_POST['newName'];
                            $newSex = $_POST['newSex'];
                            $newAccount = $_POST['newAccount'];
                            $newPassword = $_POST['newPassword'];
                            $newsql ="INSERT INTO employee (id, eId, eName, eSex, eAccount, ePassword) VALUES (".($count+1).", 'emp00".($count+1)."', '$newName', $newSex, '$newAccount', '$newPassword')";
                            if(mysqli_query($con,$newsql)){
                                echo' <script language="javascript" type="text/javascript"> alert("User name and password Added") </script>';
                            }
                            header("Location: usersetting.php");
    					}
    					?>
    					
                   
                    <!-- /. ROW  -->
                    
    			 <!-- /. PAGE INNER  -->
            </div>
         <!-- /. PAGE WRAPPER  -->
        </div>
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
               
                $('#dataTable-example').dataTable();
               
              
            });
    </script>
    
         <!-- Custom Js -->
    <script src="assets/js/custom-scripts.js"></script>
   
</body>
</html>
