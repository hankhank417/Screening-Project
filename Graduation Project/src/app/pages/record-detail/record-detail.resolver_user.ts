import { Injectable } from '@angular/core';
import { Resolve, ActivatedRouteSnapshot } from '@angular/router';
import { AuthService } from '../../auth.service';


@Injectable()
export class record_detailResolver_user implements Resolve<any> {

  constructor(private firebaseService: AuthService) {}

  resolve() {
    return new Promise((resolve, reject) => {
      this.firebaseService.getuser()
      .then(data2 => {
        resolve(data2);
      }, err => {
        reject(err);
      })
    })
  }
}
