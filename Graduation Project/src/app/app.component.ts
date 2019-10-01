// －－－－－－－－－－－－－－－－－－－－－－－－－－－
//  程式功能：引入angular fire及預設登入頁面
//  最後編輯者：汪駿華
//  最後編輯時間：2019/07/19
//  －－－－－－－－－－－－－－－－－－－－－－－－－－－
//  Function 功能描述 (ex:getName():取得名字 )：
//  initializeApp()中可以檢測使用者是否登入，若登入則跳轉到後面設定的頁面(像是login、signup等等，可以到app-routing中設定)
//  －－－－－－－－－－－－－－－－－－－－－－－－－－－

import { Component, OnInit, ViewEncapsulation } from '@angular/core';
import { Router } from '@angular/router';
import { SwUpdate } from '@angular/service-worker';

import { Events, MenuController, Platform, ToastController } from '@ionic/angular';

import { SplashScreen } from '@ionic-native/splash-screen/ngx';
import { StatusBar } from '@ionic-native/status-bar/ngx';

import { AngularFireAuth } from '@angular/fire/auth';
import { AuthService } from './auth.service';
import { Storage } from '@ionic/storage';

import { UserData } from './providers/user-data';



@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
  encapsulation: ViewEncapsulation.None
})
export class AppComponent implements OnInit {
  
  username: string;

  appPages = [
    {
      title: '首頁',
      url: '/app/tabs/main',
      icon:'home'
    },
    {
      title: '路線導航',
      url: '/app/tabs/gps',
      icon: 'navigate'
    },
    {
      title: '事件回報',
      url: '/app/tabs/report',
      icon:'megaphone'
    },
    {
      title: '支援地點',
      url: '/app/tabs/assists',
      icon:'medkit'
    },
    {
      title: '回報紀錄',
      url: '/app/tabs/record',
      icon:'list-box'
    }
  ];

  constructor(
    private menu: MenuController,
    private platform: Platform,
    private router: Router,
    private splashScreen: SplashScreen,
    private statusBar: StatusBar,
    private swUpdate: SwUpdate,
    private toastCtrl: ToastController,
    private storage: Storage,
    private authService: AuthService,
    public afAuth: AngularFireAuth,

  ) {
    this.initializeApp();
  }

  async ngOnInit() {
    this.swUpdate.available.subscribe(async res => {
      const toast = await this.toastCtrl.create({
        message: 'Update available!',
        showCloseButton: true,
        position: 'bottom',
        closeButtonText: `Reload`
      });

      await toast.present();

      toast
        .onDidDismiss()
        .then(() => this.swUpdate.activateUpdate())
        .then(() => window.location.reload());
    });
  }

  initializeApp() {
    this.platform.ready().then(() => {
      this.afAuth.user.subscribe(user => {
        if(user){ //有登入
          this.menu.enable(true);
          this.router.navigate(["/main"]);
        } else {  //沒登入
          this.menu.enable(false);
          this.router.navigate(["/tutorial"]);
        }
      }, err => {
        this.router.navigate(["/login"]);
      }, () => {
        this.splashScreen.hide();
      })
      this.statusBar.styleDefault();
    });
    // this.username = this.authService.getUserDetails().displayName;
  }


  openTutorial() {
    this.menu.enable(false);
    this.storage.set('ion_did_tutorial', false);
    this.router.navigateByUrl('/tutorial');
  }

  openLogin() {
    this.menu.enable(false);
    this.router.navigateByUrl('/login');
  }

  openAbout() {
    this.router.navigateByUrl('/about');
  }
  
  openSetting() {
    this.router.navigateByUrl('/setting');
  }

  openAccount() {
    this.router.navigateByUrl('/account');
  }

  openPrivacy() {
    this.router.navigateByUrl('/privacy');
  }

  logout(){
    this.authService.doLogout();
  }
}
