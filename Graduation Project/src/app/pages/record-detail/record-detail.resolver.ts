import { Injectable } from '@angular/core';
import { Resolve, ActivatedRouteSnapshot } from '@angular/router';
import { AuthService } from '../../auth.service';


@Injectable()
export class record_detailResolver implements Resolve<any> {

  constructor(public firebaseService: AuthService) {}

  resolve(route:ActivatedRouteSnapshot) {
    return new Promise((resolve, reject) => {
      let reportID = route.paramMap.get('id');

      this.firebaseService.report_detail(reportID)
      .then(data => {
        data.id = reportID;
        resolve(data);
      }, err => {
        reject(err);
      })
    })
  }
}
