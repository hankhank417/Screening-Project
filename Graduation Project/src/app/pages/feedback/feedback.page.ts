import { Component, OnInit } from '@angular/core';
import { NavController } from '@ionic/angular';
import { ActivatedRoute} from '@angular/router';

import { EmailComposer } from '@ionic-native/email-composer/ngx';

@Component({
  selector: 'feedback',
  templateUrl: './feedback.page.html',
  styleUrls: ['./feedback.page.scss'],
})
export class FeedbackPage implements OnInit {

    currentImage =null;
    //user data
    email: string;
    item : any;

    //email content
    subject:'';
    body:'';
    to:'jiagogododo@gmail.com';

  constructor(
    public navCtrl:NavController,
    private route: ActivatedRoute,
    public emailComposer:EmailComposer
  ) { }

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
  sendEmail(){
    let email={
      to:this.to,
      cc:[],
      bcc:[],
      attachments:[],
      subject:this.subject,
      body:this.body,
      isHtml:false,
      app:"Gmail"
    }
    this.emailComposer.open(email);
  }
}
