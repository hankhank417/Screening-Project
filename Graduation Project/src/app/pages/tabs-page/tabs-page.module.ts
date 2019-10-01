import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { IonicModule } from '@ionic/angular';

import { TabsPage } from './tabs-page';
import { TabsPageRoutingModule } from './tabs-page-routing.module';

import { AboutModule } from '../about/about.module';
import { SessionDetailModule } from '../session-detail/session-detail.module';
import { GpsModule } from '../gps/gps.module';
import { AccountModule } from '../account/account.module';
import { AssistsModule } from '../assists/assists.module';

@NgModule({
  imports: [
    AboutModule,
    CommonModule,
    IonicModule,
    SessionDetailModule,
    TabsPageRoutingModule,
    AccountModule,
    GpsModule,
    AssistsModule
  ],
  declarations: [
    TabsPage,
  ]
})
export class TabsModule { }
