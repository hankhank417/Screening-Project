import { Component, OnInit } from '@angular/core';
import { AuthService } from '../../auth.service';
import { ActivatedRoute } from '@angular/router';
import { AlertController } from '@ionic/angular';
import * as firebase from 'firebase/app';
// import 'firebase/storage';

@Component({
  selector: 'record-detail',
  templateUrl: './record-detail.page.html',
  styleUrls: ['./record-detail.page.scss'],
})
export class RecordDetailPage implements OnInit {
  item: any;
  progress: string;
  value: number;
  admin:any;
  user:any;
  
  constructor(
    private authService: AuthService,
    private route: ActivatedRoute,
    private alertCtrl: AlertController,
  ) { }

  ngOnInit() {
    this.getData();
  }

  getData(){
    this.route.data.subscribe(routeData=>{
      let data = routeData['data'];
      if(data){
        this.item = data;
        if(this.item.Processing_Progress == 'UNPROCESSED'){
          this.progress = '未處理';
          this.value = 0;
        }
        if(this.item.Processing_Progress == 'PROCESSED'){
          this.progress = '已處理';
          this.value = 1;
        }
        if(this.item.Processing_Progress == 'PROCESSING'){
          this.progress = '處理中';
          this.value = 0.5;
        }
      }
    });
    this.route.data.subscribe(routeData => {
      let data2 = routeData['data2'];
      if (data2) {
        this.user = data2;
        if(this.user.isAdmin == 1)
        {
          this.admin = 1;
        }
        else
        {
          this.admin = 0;
        }
      }
     })
  }


  //use for test :)
  setUNPROCESSED(){
    this.value = 0;
    this.authService.setPROCESS(this.item.id,'UNPROCESSED');
  }
  

  async setPROCESSING(){
    const alert = await this.alertCtrl.create({
      header: '注意',
      message: '確認受理？',
      buttons: [
        {
          text: '取消',
          role: 'cancel',
          cssClass: 'secondary',
          handler: () => {}
        },
        {
          text: '確認',
          handler: () => {
            this.value = 0.5;
            this.authService.setPROCESS(this.item.id,'PROCESSING');
          }
        }
      ]

    });
    await alert.present();
  }
  
  async setPROCESSED(){
    const alert = await this.alertCtrl.create({
      header: '注意',
      message: '確認處理完畢？',
      buttons: [
        {
          text: '取消',
          role: 'cancel',
          cssClass: 'secondary',
          handler: () => {}
        },
        {
          text: '確認',
          handler: () => {
            this.value = 1;
            this.authService.setPROCESS(this.item.id,'PROCESSED');
          }
        }
      ]

    });
    await alert.present();
  }
}
