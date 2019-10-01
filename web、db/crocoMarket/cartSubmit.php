<?php  
	session_start();
	include('db.php');

	$sql ="SELECT COUNT(*) as tcount FROM (SELECT tId FROM trade GROUP BY tId) as tradetable";
    $result_2 = mysqli_query($con, $sql);
    $row_2 = mysqli_fetch_array($result_2);
    $tcount = $row_2['tcount'];
    $sql="INSERT INTO `transactionDetails`(`id`,`tId`,`cId`,`eId`) VALUES ( ".($tcount+1).", 'tran".($tcount+1)."' ,'cus1' ,'".$_SESSION["peopleId"]."');";
    $b = mysqli_query($con,$sql);

	$sql = "SELECT peopleId, gId, quantity FROM cart WHERE peopleId = '".$_SESSION["peopleId"]."'";
    $result = mysqli_query($con,$sql);
    while ($row = mysqli_fetch_array($result)) {
    	$newNum = 0;
    	$legal = true;
    	$sql_quantity = "SELECT quantity FROM stock WHERE gId = '".$row["gId"]."'";
	    $result_quantity = mysqli_query($con,$sql_quantity);
	    while ($row_quantity = mysqli_fetch_array($result_quantity)) {
    		if (($row_quantity['quantity']-$row['quantity'])>=0){
    			$newNum = $row_quantity['quantity']-$row['quantity'];
    		}else{
    			$legal = false;
    			echo $row_quantity['quantity'];
    		}
    	}
    	if ($legal) {
            
	        $returnBill="UPDATE stock SET quantity=".$newNum." WHERE gId='".$row["gId"]."'";
	        $a = mysqli_query($con,$returnBill);

	        $sql ="SELECT COUNT(id) as count FROM trade";
	        $result_1 = mysqli_query($con, $sql);
	        $row_1 = mysqli_fetch_array($result_1);
	        $count = $row_1['count'];
	        $sq="INSERT INTO `trade`(`id`,`tId`,`gId`,`quantity`,`tradeTime`) 
	            VALUES ( ".($count+1).",'tran".($tcount+1)."' ,'".$row['gId']."' ,".$row['quantity'].", NOW());";
	        if (mysqli_query($con,$sq)) {
	            echo "<br>Insert successfully";
	        }
	    }
    }
    $sql="DELETE FROM `cart` WHERE peopleId = '".$_SESSION["peopleId"]."'";
	$c = mysqli_query($con,$sql);
    header("Location: cart.php");
?>