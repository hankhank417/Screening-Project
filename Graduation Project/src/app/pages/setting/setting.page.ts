import { Component, OnInit } from '@angular/core';
import { Router , ActivatedRoute} from '@angular/router';
import { AuthService } from '../../auth.service';

@Component({
  selector: 'setting',
  templateUrl: './setting.page.html',
  styleUrls: ['./setting.page.scss'],
})
export class SettingPage implements OnInit {

  Route_isToggled:boolean;
  Highway_isToggled:boolean;
  Toll_isToggled:boolean;

  item:any;
  constructor(
    private router:Router,
    private route:ActivatedRoute,
    private authService:AuthService,
  ) { }

  ngOnInit() {
    if (this.route && this.route.data) {
      this.getData();
    }
  }

  getData(){
    this.route.data.subscribe(routeData => {
    let data = routeData['data'];
    if (data) {
      this.item = data;
      this.Route_isToggled = this.item.Route_isToggled;
      this.Highway_isToggled = this.item.Highway_isToggled;
      this.Toll_isToggled = this.item.Toll_isToggled;
     }
    })
  }

  togglechanged(){
    this.authService.updateSettings(this.Route_isToggled,this.Highway_isToggled,this.Toll_isToggled);
  }

}
