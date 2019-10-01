import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Routes, RouterModule } from '@angular/router';

import { IonicModule } from '@ionic/angular';

import { RecordDetailPage } from './record-detail.page';
import { record_detailResolver} from './record-detail.resolver'
import { record_detailResolver_user } from './record-detail.resolver_user'


const routes: Routes = [
  {
    path: '',
    component: RecordDetailPage,
    resolve:{
      data:record_detailResolver,
      data2:record_detailResolver_user
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
  declarations: [RecordDetailPage],
  providers:[record_detailResolver,record_detailResolver_user]
})
export class RecordDetailPageModule {}
