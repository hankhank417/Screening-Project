import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { IonicModule } from '@ionic/angular';
import { FormsModule } from '@angular/forms';

import { AssistsPage } from './assists';
import { AssistsPageRoutingModule } from './assists-routing.module';
import { AssistsFilterPage } from '../assists-filter/assists-filter';

@NgModule({
  imports: [
    CommonModule,
    IonicModule,
    AssistsPageRoutingModule,
    FormsModule
  ],
  declarations: [
    AssistsPage,
    AssistsFilterPage
  ],
  entryComponents: [
    AssistsFilterPage
  ]
})
export class AssistsModule { }
