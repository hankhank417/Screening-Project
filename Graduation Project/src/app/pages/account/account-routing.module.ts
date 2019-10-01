import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { AccountPage } from './account';
import { accountResolver } from './account.resolver';


const routes: Routes = [
  {
    path: '',
    component: AccountPage,
    resolve: {
      data: accountResolver
    }
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
  providers: [
    accountResolver,
  ]
})
export class AccountPageRoutingModule { }
