import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Routes, RouterModule } from '@angular/router';

import { IonicModule } from '@ionic/angular';

import { FeedbackPage } from './feedback.page';
import { accountResolver } from '../account/account.resolver';
import { EmailComposer } from '@ionic-native/email-composer/ngx';


const routes: Routes = [
  {
    path: '',
    component: FeedbackPage,
    resolve: {
      data: accountResolver
    }

  }
];

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    RouterModule.forChild(routes)
  ],
  declarations: [FeedbackPage],
  providers:[
    accountResolver,
    EmailComposer,
  ]

})
export class FeedbackPageModule {}
