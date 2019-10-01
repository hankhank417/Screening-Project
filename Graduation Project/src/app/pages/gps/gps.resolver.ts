import { Injectable } from '@angular/core';
import { Resolve } from '@angular/router';
import { AuthService } from '../../auth.service';

@Injectable()
export class gpsResolver implements Resolve<any> {

  constructor(private firebaseService: AuthService) {}

  resolve() {
    return this.firebaseService.getreport();
  }
}
