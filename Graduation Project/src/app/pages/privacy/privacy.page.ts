import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'privacy',
  templateUrl: './privacy.page.html',
  styleUrls: ['./privacy.page.scss'],
})
export class PrivacyPage implements OnInit {

  constructor(private router: Router,) { }

  ngOnInit() {
  }

  btnClick()
  {
    this.router.navigateByUrl('/privacy2');
  }
}
