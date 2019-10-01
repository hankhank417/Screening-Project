import { Injectable } from '@angular/core';
import { Resolve, ActivatedRouteSnapshot } from '@angular/router';
import { AuthService } from '../../auth.service';


@Injectable()
export class accountResolver implements Resolve<any> {

  constructor(private firebaseService: AuthService) {}

  resolve() {
    return new Promise((resolve, reject) => {
      this.firebaseService.getuser()
      .then(data => {
        resolve(data);
      }, err => {
        reject(err);
      })
    })
  }
}
