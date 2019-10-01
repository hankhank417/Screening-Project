import { Component, OnInit } from '@angular/core';
import { ActivatedRoute , Router} from '@angular/router';
import { AuthService } from '../../auth.service';
import { MenuController } from '@ionic/angular';

@Component({
  selector: 'record',
  templateUrl: './record.page.html',
  styleUrls: ['./record.page.scss'],
})
export class RecordPage implements OnInit {
items : Array<any>;
userUID : any;
user:any;
admin:any;


  constructor(
    public menu: MenuController,
    private route:ActivatedRoute,
    private authService:AuthService,
    private router:Router,
  ){ 
    this.menu.enable(true);
  }

  ngOnInit() {
    if(this.route && this.route.data){
      this.getData();
    }
    this.userUID = this.authService.getUserData().uid;
  }

  getData(){
    this.route.data.subscribe(routeData => {
      routeData['data'].subscribe(
        data => {
          this.items = data;
        }
      )
    });
    this.route.data.subscribe(routeData => {
      let data2 = routeData['data2'];
      if (data2) {
        this.user = data2;
        if(this.user.isAdmin == 1)
        {
          this.admin = 1;
        }
        else
        {
          this.admin = 0;
        }
      }
     })
  }


}
