<?php  
session_start();  
if(!isset($_SESSION["user"]))
{
 header("location: ../index.php");
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
    <script src="./assets/js/Chart.bundle.js"></script>
    <script src="./assets/js/utils.js"></script>
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
                    <li><a class="active-menu" href="profitChart.php"><i class="far fa-chart-bar fa-2x"></i>Profit Chart</a></li>
                    <li><a href="sendletter.php"><i class="far fa-envelope fa-2x"></i>Send Letter</a></li>
                    <li><a href="Bill.php"><i class="fas fa-qrcode fa-2x"></i>Bill</a></li>
                </ul>
            </div>
        </nav>
        <!-- /. NAV SIDE  -->
        <div id="page-wrapper">
            <div id="page-inner">
                <div class="row">
                    <div class="col-md-12">
                        <h1 class="page-header">
                            Chart <small>Profit</small>
                        </h1>
                    </div>
                    <div class="col-md-12">
                        <a href="profitChart.php" class='btn btn-primary'><i class='far fa-chart-bar'></i>  Profit</a>
                        <a href="tradeChart.php" class='btn btn-primary'><i class='far fa-chart-bar'></i>  Trade</a>
                        <a href="returnChart.php" class='btn btn-primary'><i class='far fa-chart-bar'></i>  Return</a>
                        <a href="purchaseChart.php" class='btn btn-primary'><i class='far fa-chart-bar'></i>  Purchase</a>
                        <br><br>
                        <canvas id="canvas" width="1425" height="712" class="chartjs-render-monitor" style="display: block; height: 570px; width: 1140px;"></canvas>
                        <script>
                            <?php

                            include('db.php');

                            // 添加底部橫條時間
                            $query = "SELECT DATE_FORMAT(rDate, '%Y/%m') AS timeLine FROM returnOrder
                                      UNION 
                                      SELECT DATE_FORMAT(pDate, '%Y/%m') FROM purchaseOrder
                                      UNION
                                      SELECT DATE_FORMAT(tradeTime, '%Y/%m') FROM trade  
                                      ORDER BY `timeLine` ASC";
                            $result = mysqli_query($con, $query);
                            if (!$result) {
                                printf("Error: %s\n", mysqli_error($con));
                                exit();
                            }
                            $data = array();
                            $Labels = "";
                            while ($row = mysqli_fetch_array($result)){
                                $Labels .= '"'.$row['timeLine'].'",';
                                $data[$row['timeLine']] = $row['timeLine'];
                            }
                            // print_r($Labels);
                            // print_r($data);
                            // echo "<br>";echo "<br>";

                            // 添加項目
                            $query = "SELECT goodFullName FROM purchaseProduct INNER JOIN stock ON stock.gId=purchaseProduct.gId
                                      UNION 
                                      SELECT goodFullName FROM returnProduct INNER JOIN stock ON stock.gId=returnProduct.gId
                                      UNION
                                      SELECT goodFullName FROM trade INNER JOIN stock ON stock.gId=trade.gId
                                      GROUP BY goodFullName";
                            $result = mysqli_query($con, $query);
                            if (!$result) {
                                printf("Error: %s\n", mysqli_error($con));
                                exit();
                            }
                            $type = array();
                            $type[] = "profit";
                            $data2 = array();
                            while ($row = mysqli_fetch_array($result)){
                                $type[] = $row['goodFullName'];
                                
                                foreach($data as $value) {
                                    $data2[$value][$row['goodFullName']] = 0;
                                    $data2[$value]['profit'] = 0;
                                }
                            }

                            // 新增trade金額
                            $query = "SELECT goodFullName, SUM(trade.quantity*price) as mul, DATE_FORMAT(tradeTime, '%Y/%m') AS timeLine
                                      FROM trade INNER JOIN stock ON trade.gId = stock.gId
                                      GROUP BY goodFullName,timeLine
                                      ORDER BY timeLine,goodFullName";
                            $result = mysqli_query($con, $query);
                            if (!$result) {
                                printf("Error: %s\n", mysqli_error($con));
                                exit();
                            }
                            while ($row = mysqli_fetch_array($result)){
                                $data2[$row['timeLine']][$row['goodFullName']] += $row['mul'];
                                $data2[$row['timeLine']]['profit'] += $row['mul'];
                            }

                            // 新增purchase金額
                            $query = "SELECT goodFullName, SUM(costPrice*purchaseQuantity) as mul, DATE_FORMAT(pDate, '%Y/%m') AS timeLine
                                      FROM purchaseOrder 
                                      INNER JOIN purchaseProduct ON purchaseProduct.pId = purchaseOrder.pId
                                      INNER JOIN stock ON purchaseProduct.gId=stock.gId
                                      GROUP BY goodFullName,timeLine
                                      ORDER BY timeLine,goodFullName";
                            $result = mysqli_query($con, $query);
                            if (!$result) {
                                printf("Error: %s\n", mysqli_error($con));
                                exit();
                            }
                            while ($row = mysqli_fetch_array($result)){
                                $data2[$row['timeLine']][$row['goodFullName']] -= $row['mul'];
                                $data2[$row['timeLine']]['profit'] -= $row['mul'];
                            }

                            // 新增return金額
                            $query = "SELECT goodFullName, SUM(costPrice*returnQuantity) as mul, DATE_FORMAT(rDate, '%Y/%m') AS timeLine
                                      FROM returnOrder INNER JOIN returnProduct ON returnProduct.rId = returnOrder.rId
                                      INNER JOIN stock ON returnProduct.gId=stock.gId
                                      GROUP BY goodFullName,timeLine
                                      ORDER BY timeLine,goodFullName";
                            $result = mysqli_query($con, $query);
                            if (!$result) {
                                printf("Error: %s\n", mysqli_error($con));
                                exit();
                            }
                            while ($row = mysqli_fetch_array($result)){
                                $data2[$row['timeLine']][$row['goodFullName']] += $row['mul'];
                                $data2[$row['timeLine']]['profit'] += $row['mul'];
                            }
                            ?>

                            var color = Chart.helpers.color;
                            var barChartData = {
                                labels: [<?php echo $Labels; ?>],
                                datasets: [
                                    <?php 
                                        // 定義每種東西顏色
                                        $color_count = 0;
                                        $color = array("red", "yellow", "blue", "green", "orange", "gray", "purple");
                                        foreach ($type as $Type) {
                                            echo "
                                                {
                                                    label : '$Type',
                                                    backgroundColor: color(window.chartColors.$color[$color_count]).alpha(0.5).rgbString(),
                                                    borderColor: window.chartColors.$color[$color_count],
                                                    borderWidth: 1,
                                                    data: [";
                                                            foreach ($data2 as $value) {
                                                                echo "$value[$Type],";
                                                            }

                                            echo "
                                                          ]
                                                },";
                                            $color_count++;
                                            if ($color_count>=7) {$color_count = 0;}
                                        }
                                    ?>
                                ]
                            };
                            
                            window.onload = function() {
                                var ctx = document.getElementById('canvas').getContext('2d');
                                window.myBar = new Chart(ctx, {
                                    type: 'bar',
                                    data: barChartData,
                                    options: {
                                        responsive: true,
                                        legend: {
                                            position: 'top',
                                        },
                                        title: {
                                            display: false,
                                            text: ''
                                        },
                                        scales: {
                                            yAxes: [{
                                                ticks: {
                                                    beginAtZero:true
                                                }
                                            }]
                                        }
                                    }
                                });
                            };
                        </script>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <!-- /. WRAPPER  -->
    <!-- JS Scripts-->
    <!-- jQuery Js -->
    <script src="assets/js/jquery-1.10.2.js"></script>
    <!-- Bootstrap Js -->
    <script src="assets/js/bootstrap.min.js"></script>
    <!-- Metis Menu Js -->
    <script src="assets/js/jquery.metisMenu.js"></script>
    <!-- Morris Chart Js -->
    <script src="assets/js/morris/raphael-2.1.0.min.js"></script>
    <script src="assets/js/morris/morris.js"></script>
    <!-- Custom Js -->
    <script src="assets/js/custom-scripts.js"></script>
</body>
</html>