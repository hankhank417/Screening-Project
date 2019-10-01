import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { TabsPage } from './tabs-page';

const routes: Routes = [
  {
    path: 'tabs',
    component: TabsPage,
    children: [
      {
        path: '',
        redirectTo: '/app/tabs/tutorial',
        pathMatch: 'full'
      },
      {
        path: 'main',
        children: [{
          path: '',
          loadChildren: '../main/main.module#MainPageModule'
        }]
      },
      {
        path: 'gps',
        children: [{
          path: '',
          loadChildren: '../gps/gps.module#GpsModule'
        }]
      },
      {
        path: 'report',
        children: [{
          path: '',
          loadChildren: '../report/report.module#ReportPageModule'
        }]
      },
      {
        path: 'account',
        children: [{
          path: '',
          loadChildren: '../account/account.module#AccountModule'
        }]
      },
      {
        path: 'record',
        children: [{
          path: '',
          loadChildren: '../record/record.module#RecordPageModule'
        }]
      },
      {
        path: 'assists',
        children: [{
          path: '',
          loadChildren: '../assists/assists.module#AssistsModule'
        }]
      }
    ]
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class TabsPageRoutingModule { }

