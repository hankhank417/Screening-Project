//  －－－－－－－－－－－－－－－－－－－－－－－－－－－
//  程式功能：sidebar link
//  最後編輯者：蔡宗諺
//  最後編輯時間：2019/07/15
//  －－－－－－－－－－－－－－－－－－－－－－－－－－－
//  Function 功能描述 (ex:getName():取得名字 )：
// 
//  －－－－－－－－－－－－－－－－－－－－－－－－－－－

import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

const routes: Routes = [
  {
    path: '',
    redirectTo: '/tutorial',
    pathMatch: 'full'
  },
  {
    path: 'app',
    loadChildren: './pages/tabs-page/tabs-page.module#TabsModule'
  },
  { path: 'main',
    loadChildren: './pages/main/main.module#MainPageModule'
  },
  {
    path: 'login',
    loadChildren: './pages/login/login.module#LoginModule'
  },
  {
    path: 'signup',
    loadChildren: './pages/signup/signup.module#SignUpModule'
  },
  {
    path: 'tutorial',
    loadChildren: './pages/tutorial/tutorial.module#TutorialModule'
  },
  {
    path: 'about',
    loadChildren: './pages/about/about.module#AboutModule'
  },
  { 
    path: 'report', 
    loadChildren: './pages/report/report.module#ReportPageModule' 
  },
  //{
    //path: 'privacy',
    //loadChildren: './pages/privacy/privacy.module#PrivacyModule'
  //}
  {
    path: 'account',
    loadChildren: './pages/account/account.module#AccountModule'
  },
  { 
    path: 'gps', 
    loadChildren: './pages/gps/gps.module#GpsModule' 
  },
  { 
    path: 'record', 
    loadChildren: './pages/record/record.module#RecordPageModule' 
  },
  { 
    path: 'record-detail/:id', 
    loadChildren: './pages/record-detail/record-detail.module#RecordDetailPageModule' 
  },
  {
    path: 'setting',
    loadChildren: './pages/setting/setting.module#SettingPageModule'
  },
  {
    path: 'privacy',
    loadChildren: './pages/privacy/privacy.module#PrivacyPageModule'
  },
  {
    path: 'privacy2',
    loadChildren: './pages/privacy2/privacy2.module#Privacy2PageModule'
  },
  { 
    path: 'assists', 
    loadChildren: './pages/assists/assists.module#AssistsModule' 
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {}
