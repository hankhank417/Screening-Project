import { Component, OnInit } from '@angular/core';
import { Router , ActivatedRoute} from '@angular/router';

import { AlertController, MenuController } from '@ionic/angular';

import { UserData } from '../../providers/user-data';
import { AuthService } from '../../auth.service';

import { LoadingController, ToastController } from '@ionic/angular';
import { ImagePicker } from '@ionic-native/image-picker/ngx';
import { WebView } from '@ionic-native/ionic-webview/ngx';


@Component({
  selector: 'page-account',
  templateUrl: 'account.html',
  styleUrls: ['./account.scss'],
})
export class AccountPage implements OnInit {
  
  
  username: string;
  email: string;
  phone: string;
  usr: string;
  history: any;
  item : any;
  image:any;
  

  constructor(
    private route: ActivatedRoute,
    private authService : AuthService,
    public alertCtrl: AlertController,
    public userData: UserData,
    private menu: MenuController,
    private router: Router,
    private webview: WebView,
    private imagePicker: ImagePicker,
    public toastCtrl: ToastController,
    public loadingCtrl: LoadingController,

  ) {
    this.menu.enable(true)
  }


  ngOnInit() {
      if (this.route && this.route.data) {
        this.getData();
      }
    }

  getData(){
    this.route.data.subscribe(routeData => {
    let data = routeData['data'];
    if (data) {
      this.item = data;
    }
    })
  }

  updatePicture() {
    this.imagePicker.hasReadPermission()
    .then((result) => {
      if(result == false){
        // no callbacks required as this opens a popup which returns async
        this.imagePicker.requestReadPermission();
      }
      else if(result == true){
        this.imagePicker.getPictures({
          maximumImagesCount: 1
        }).then(
          (results) => {
            for (var i = 0; i < results.length; i++) {
              this.uploadImageToFirebase(results[i]);
            }
          }, (err) => console.log(err)
        );
      }
    }, (err) => {
      console.log(err);
    });
  }

  // Present an alert with the current username populated
  // clicking OK will update the username and display it
  // clicking Cancel will close the alert and do nothing
  async changeUsername() {
    const alert = await this.alertCtrl.create({
      header: '編輯名稱',
      buttons: [
        '取消',
        {
          text: '確定',
          handler: (data: any) => {
            this.authService.updateName(data.username).then(
            ()=>window.location.reload()
          )
          }
        }
      ],
      inputs: [
        {
          type: 'text',
          name: 'username',
          value: this.item.Name,
          placeholder: '王小明'
        }
      ]
    });
    await alert.present();
  }


  async changeEmail() {
    const alert = await this.alertCtrl.create({
      header: '修改電子郵件(登入)',
      inputs: [
        {
          type: 'text',
          name: 'useremail',
          value: this.item.Email,
          
        }
      ],
      buttons: [
        '取消',
        {
          text: '確定',
          handler: data => {
            this.authService.getUserData().updateEmail(data.useremail).then(()=>
            this.authService.updateEmail(data.useremail).then(
              ()=>window.location.reload()
            )
            )
            
          }
        }
      ],
      
    });
    await alert.present();
    }

    async changePassword() {
      const alert = await this.alertCtrl.create({
        header: '修改密碼(登入)',
        inputs: [
          {
            type: 'text',
            name: 'userpassword',
            value: this.item.Password,
            
          }
        ],
        buttons: [
          '取消',
          {
            text: '確定',
            handler: data => {
              this.authService.getUserData().updatePassword(data.userpassword).then(()=>
              this.authService.updatePassword(data.userpassword).then(
                ()=>window.location.reload()
              )
              )
              
            }
          }
        ],
        
      });
      await alert.present();
      }

  logout(){
    this.authService.doLogout();
  }


  async changePhone() {
    const alert = await this.alertCtrl.create({
      header: '修改電話號碼',
      inputs: [
        {
          type: 'text',
          name: 'userphone',
          value: this.item.Phone,
          placeholder: '09xxxxxxxx'
        }
      ],
      buttons: [
        '取消',
        {
          text: '確定',
          handler: data => {
            this.authService.updatePhone(data.userphone).then(
              ()=>window.location.reload()
            )
          }
        }
      ],
      
    });
    await alert.present();
    }
    async uploadImageToFirebase(image){
      const loading = await this.loadingCtrl.create({
        message: 'Please wait...'
      });
      const toast = await this.toastCtrl.create({
        message: 'Image was updated successfully',
        duration: 3000
      });
      this.presentLoading(loading);
      let image_src = this.webview.convertFileSrc(image);
      let randomId = Math.random().toString(36).substr(2, 5);
  
      //uploads img to firebase storage
      this.authService.uploadImage(image_src, randomId)
      .then(photoURL => {
        this.image = photoURL;
        loading.dismiss();
        toast.present();
      }, err =>{
        console.log(err);
      })
    }
  
    async presentLoading(loading) {
      return await loading.present();
    }

  


}

