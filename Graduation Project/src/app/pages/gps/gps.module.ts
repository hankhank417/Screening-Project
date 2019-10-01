import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { IonicModule } from '@ionic/angular';

import { GpsPage } from './gps';
import { GpsPageRoutingModule } from './gps-routing.module';
import { gpsResolver } from './gps.resolver';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    GpsPageRoutingModule
  ],
  declarations: [
    GpsPage
  ],
  providers: [
    gpsResolver,
    GpsPage
  ]
})
export class GpsModule { }
