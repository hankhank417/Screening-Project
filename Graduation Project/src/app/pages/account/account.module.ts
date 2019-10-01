import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { IonicModule } from '@ionic/angular';
import { Routes, RouterModule } from '@angular/router';

import { AccountPage } from './account';
import { AccountPageRoutingModule } from './account-routing.module';
import { accountResolver } from './account.resolver';

@NgModule({
  imports: [
    CommonModule,
    IonicModule,
    AccountPageRoutingModule

  ],
  declarations: [
    AccountPage
  ],
  providers:[
    accountResolver
  ]
})
export class AccountModule { }
