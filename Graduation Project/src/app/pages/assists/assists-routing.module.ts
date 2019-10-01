import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { AssistsPage } from './assists';


const routes: Routes = [
  {
    path: '',
    component: AssistsPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class AssistsPageRoutingModule { }
