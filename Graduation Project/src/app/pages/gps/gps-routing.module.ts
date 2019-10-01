import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { GpsPage } from './gps';
import { gpsResolver } from './gps.resolver';


const routes: Routes = [
  {
    path: '',
    component: GpsPage,
    resolve: {
      data: gpsResolver
    }
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
  providers: [
    gpsResolver
  ]
})
export class GpsPageRoutingModule { }
