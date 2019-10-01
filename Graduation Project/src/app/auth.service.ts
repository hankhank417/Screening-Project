import { Injectable } from '@angular/core';
import { LoadingController, ToastController, AlertController } from '@ionic/angular';

import * as firebase from 'firebase/app';
import { AngularFireAuth } from '@angular/fire/auth';
import { AngularFirestore , AngularFirestoreCollection } from '@angular/fire/firestore';
import 'firebase/storage';
import { Observable } from 'rxjs';


export interface Item { name: string; }



@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private snapshotChangesSubscription : any;

  constructor(
    public afAuth: AngularFireAuth,
    public afs: AngularFirestore,
    private alertCtrl: AlertController,

  ){}

  doRegister(value){
   return new Promise<any>((resolve, reject) => {
     firebase.auth().createUserWithEmailAndPassword(value.email, value.password)
     .then(
       res => resolve(res),
       err => reject(err))
       .then(function(){
        var user = firebase.auth().currentUser; 
        return user.updateProfile({
           displayName: value.name
         })
       })
       
   })
  }

  doLogin(value){
   return new Promise<any>((resolve, reject) => {
     firebase.auth().signInWithEmailAndPassword(value.email, value.password)
     .then(
       res => resolve(res),
       err => reject(err))
   })
  }


  //登出
  doLogout(){
    return new Promise((resolve, reject) => {
      if(firebase.auth().currentUser){
        firebase.auth().signOut()
      .then(() => {
        resolve();
      }).catch((error) => {
        console.log(error);
        reject();
      })};
    })
  }

  //把使用者在註冊頁面輸入的資訊輸入到資料庫
  createUser(value){
    return new Promise<any>((resolve,reject)=>{
      let currentUser = firebase.auth().currentUser;
      this.afs.collection('user').doc(currentUser.uid).set({
        Name:value.Name,
        SSID:value.SSID,
        Email:value.Email,
        Password:value.Password,
        Phone:value.Phone,
        Route_isToggled:true,
        Highway_isToggled:false,
        Toll_isToggled:false,
      })
      .then(
        res => resolve(res),
        err => reject(err)
      )
    })

  }

//創立回報事件
  createEvent(value){
    return new Promise<any>((resolve,reject) =>{
      let currentUser = firebase.auth().currentUser;
      let time = new Date();
      let mon = time.getMonth()+1;
      let min = time.getMinutes();

      if(min < 10){
        this.afs.collection('report').add({
        Reporter_Name:value.reporter_name,
        Reporter_UID:currentUser.uid,
        Reporter_Phone:value.reporter_phone,
        Event_location:value.event_location,
        Event_description:value.event_description,
        lat:value.lat,
        lng:value.lng,        
        Report_Date:time.getFullYear() + "/" + mon + "/" + time.getDate(),
        Report_Time:time.getHours() + ":" + "0" +min,
        Processing_Progress:'UNPROCESSED',
        })
      }
      else{
        this.afs.collection('report').add({
        Reporter_Name:value.reporter_name,
        Reporter_UID:currentUser.uid,
        Reporter_Phone:value.reporter_phone,
        Event_location:value.event_location,
        Event_description:value.event_description,
        lat:value.lat,
        lng:value.lng,
        Report_Date:time.getFullYear() + "/" + mon + "/" + time.getDate(),
        Report_Time:time.getHours() + ":" + min,
        Processing_Progress:'UNPROCESSED',
        })
      }


    })
  }

  //更新使用者手機號碼
  updatePhone(value){
    return new Promise<any>((resolve,reject)=>{
      let currentUser = firebase.auth().currentUser;
      this.afs.collection('user').doc(currentUser.uid).update({
        Phone: value,
      })
      .then(
        res => resolve(res),
        err => reject(err)
      )
    })
  }

  //更新使用者名稱
  updateName(value){
    return new Promise<any>((resolve,reject)=>{
      let currentUser = firebase.auth().currentUser;
      this.afs.collection('user').doc(currentUser.uid).update({
        Name: value,
      })
      .then(
        res => resolve(res),
        err => reject(err)
      )
    })
  }

  //更新使用者EMAIL，登入時也會修改
  updateEmail(value){
    return new Promise<any>((resolve,reject)=>{
      let currentUser = firebase.auth().currentUser;
      this.afs.collection('user').doc(currentUser.uid).update({
        Email: value,
      })
      .then(
        res => resolve(res),
        err => reject(err)
      )
    })
  }

  //更新使用者密碼，登入時也會修改
  updatePassword(value){
    return new Promise<any>((resolve,reject)=>{
      let currentUser = firebase.auth().currentUser;
      this.afs.collection('user').doc(currentUser.uid).update({
        Password: value,
      })
      .then(
        res => resolve(res),
        err => reject(err)
      )
    })
  }

  //更新使用者設定
  updateSettings(route,highway,toll){
    return new Promise<any>((resolve,reject)=>{
      let currentUser = firebase.auth().currentUser;
      this.afs.collection('user').doc(currentUser.uid).update({
        Route_isToggled:route,
        Highway_isToggled:highway,
        Toll_isToggled:toll
      })
    })
  }

  // getTasks(){
  //   return new Promise<any>((resolve, reject) => {
  //     this.afAuth.user.subscribe(currentUser => {
  //       if(currentUser){
  //         this.snapshotChangesSubscription = this.afs.collection('user').doc(currentUser.uid).snapshotChanges();
  //         resolve(this.snapshotChangesSubscription);
  //       }
  //     })
  //   })
  // }


  //訂閱使用者，並取得使用者之資訊
  getuser(){
    return new Promise<any>((resolve, reject) => {
      this.afAuth.user.subscribe(currentUser => {
        if(currentUser){
          this.snapshotChangesSubscription = this.afs.doc<any>('user/' + currentUser.uid).valueChanges()
          .subscribe(snapshots => {
            resolve(snapshots);
          }, err => {
            reject(err)
          })
        }
      })
    });
  }

  report_detail(reportID){
    return new Promise<any>((resolve, reject) => {
      this.afAuth.user.subscribe(currentUser => {
        if(currentUser){
          this.snapshotChangesSubscription = this.afs.doc<any>('report/' + reportID).valueChanges()
          .subscribe(snapshots => {
            resolve(snapshots);
          }, err => {
            reject(err)
          })
        }
      })
    });
  }

  //取得回報之資料
  getreport(){
    return new Promise<any>((resolve, reject) => {
      this.afAuth.user.subscribe(currentUser => {
        if(currentUser){
          this.snapshotChangesSubscription = this.afs.collection('report').snapshotChanges();
          resolve(this.snapshotChangesSubscription);
        }
      })
    })
  }


  setPROCESS(id,PROCESS){
    return new Promise<any>((resolve,reject) =>{
      this.afs.collection('report').doc(id).update({
        Processing_Progress:PROCESS,
      })
    })
  }


  getUserData(){ 
    var user = firebase.auth().currentUser;
    return user;
  }

  async doReport(value){  //顯示回報成功的警告欄
    this.createEvent(value);

    const alert = await this.alertCtrl.create({
      header: "事件地點 : " + value.event_location,
      message: "事件概述 : " + value.event_description,
      buttons: [
        {
          text:"yes",
          handler: () => {}
        }
      ]
      });
      await alert.present();
    
  }

  uploadImage(imageURI, randomId){
    return new Promise<any>((resolve, reject) => {
      let storageRef = firebase.storage().ref();
      let imageRef = storageRef.child('image').child(randomId);
      this.encodeImageUri(imageURI, function(image64){
        imageRef.putString(image64, 'data_url')
        .then(snapshot => {
          snapshot.ref.getDownloadURL()
          .then(res => resolve(res))
        }, err => {
          reject(err);
        })
      })
    })
  }
  encodeImageUri(imageUri, callback) {
    var c = document.createElement('canvas');
    var ctx = c.getContext("2d");
    var img = new Image();
    img.onload = function () {
      var aux:any = this;
      c.width = aux.width;
      c.height = aux.height;
      ctx.drawImage(img, 0, 0);
      var dataURL = c.toDataURL("image/jpeg");
      callback(dataURL);
    };
    img.src = imageUri;
  };

}
