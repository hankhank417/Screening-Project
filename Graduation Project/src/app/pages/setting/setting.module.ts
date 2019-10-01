import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Routes, RouterModule } from '@angular/router';

import { IonicModule } from '@ionic/angular';

import { SettingPage } from './setting.page';
import { accountResolver } from '../account/account.resolver'

const routes: Routes = [
  {
    path: '',
    component: SettingPage,
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
  declarations: [SettingPage],
  providers: [
    accountResolver,
  ]
})
export class SettingPageModule {}
