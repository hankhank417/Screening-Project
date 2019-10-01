import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Routes, RouterModule } from '@angular/router';

import { IonicModule } from '@ionic/angular';

import { RecordPage } from './record.page';
import { recordResolver } from '../record/record.resolver';
import { record_detailResolver_user } from '../record-detail/record-detail.resolver_user';

const routes: Routes = [
  {
    path: '',
    component: RecordPage,
    resolve:{
      data: recordResolver,
      data2: record_detailResolver_user,
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
  declarations: [RecordPage],
  providers:[
    recordResolver,
    record_detailResolver_user
  ]
})
export class RecordPageModule {}
