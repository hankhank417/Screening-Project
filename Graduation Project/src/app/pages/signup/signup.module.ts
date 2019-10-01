// －－－－－－－－－－－－－－－－－－－－－－－－－－－
// 程式功能：註冊會員.TS
// 最後編輯者：汪駿華
// 最後編輯時間：2019/07/19
// －－－－－－－－－－－－－－－－－－－－－－－－－－－
// Function 功能描述 (ex:getName():取得名字 )：
// 
// －－－－－－－－－－－－－－－－－－－－－－－－－－－
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { IonicModule } from '@ionic/angular';

import { SignupPage } from './signup';
import { SignupPageRoutingModule } from './signup-routing.module';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    SignupPageRoutingModule,
    ReactiveFormsModule,
  ],
  declarations: [
    SignupPage,
  ]
})
export class SignUpModule { }
