import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'privacy2',
  templateUrl: './privacy2.page.html',
  styleUrls: ['./privacy2.page.scss'],
})
export class Privacy2Page implements OnInit {

  language: any = 'tw';

  constructor(

  ) { }

  ngOnInit() {
  }

  changeLang($event){
    this.language = $event.target.value;
    console.log($event.target.value);
  }

}