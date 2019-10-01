<header>
	<div class="top-menu">
		<ul class="left-area welcome-area">
			<li class="hello-blog">哈囉，歡迎來到Croco Market</li>
		</ul>
		<div class="right-area">
			<div class="src-area" style="text-align:center;">
				<li><a href="./login.php">
					<?php
					if (!isset($_SESSION["user"])){
						echo "會員登入";
					}else{
						echo "Hello ! &nbsp;".$_SESSION['user'];
					}
					?>
				</a></li>
			</div>
			<?php
				if (isset($_SESSION["user"])) {
					echo "<div class='src-area' style='text-align:center;'>";
					echo "<li><a href='./admin/logout.php'>";
					echo "登出";
					echo "</a></li>";
					echo "</div>";
				}
			?>
			<ul class="social-icons">
				<li><a href="./cart.php"><i class="fas fa-shopping-cart fa-lg"></i></a></li>
				<li><a href="https://www.facebook.com/caobeiNSYSU/?hc_ref=ARQYmNjdzci4bTCsucuccYXg6-QR5MiGTRJyxOJHJ-DWuAOLbCYm6E2sGr92CXfUEQE&fref=nf"><i class="fab fa-facebook-square fa-lg"></i></a></li>
				<li><a href="https://twitter.com/jk_rowling"><i class="fab fa-twitter-square fa-lg"></i></a></li>
				<li><a href="https://www.instagram.com/troyesivan/?hl=zh-tw"><i class="fab fa-instagram fa-lg"></i></a></li>
			</ul>
		</div>
	</div>
	<div class="middle-menu center-text"><a href="#" class="logo"><img src="images/logo.png" width="250%" alt="Logo Image"></a></div>
		<div class="bottom-area">
		<div class="menu-nav-icon" data-nav-menu="#main-menu"><i class="ion-navicon"></i></div>
		<ul class="main-menu visible-on-click" id="main-menu">
			</li>
			<li><a href="index.php">首頁</a></li>
			<li><a href="shop.php">商店</a></li>
			<li><a href="store.php">門市搜尋</a></li>
			<li><a href="aboutCroco.php">關於Croco</a></li>
			<li><a href="contact.php">聯繫我們</a></li>
		</ul>
	</div>
</header>