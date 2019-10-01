import { Component, OnInit, ViewChild, ElementRef,AfterViewInit } from '@angular/core';
import { ActivatedRoute , Router} from '@angular/router';
import { LoadingController, ToastController, AlertController } from '@ionic/angular';
import { Geolocation } from '@ionic-native/geolocation/ngx';
import { AuthService } from '../../auth.service';
import { Validators, FormBuilder, FormGroup, FormControl } from '@angular/forms';
import {
  GoogleMaps,
  GoogleMap,
  GoogleMapsEvent,
  GoogleMapOptions,
  CameraPosition,
  MarkerOptions,
  Marker
} from '@ionic-native/google-maps';

declare var google;



@Component({
  selector: 'report',
  templateUrl: './report.page.html',
  styleUrls: ['./report.page.scss'],
})
export class ReportPage implements OnInit,AfterViewInit {

  @ViewChild('mapCanvas') mapElement: ElementRef;
  item : any;
  userwho : string;
  validations_form: FormGroup;
  myLocation: any;
  map: any;

  myLatutide: any;
  myLongitude: any;
  i = 0;
  deltaLat: any;
  deltaLng: any;
  mark_lat: number;
  mark_lng: number;
  marker : any;

  // google:any;

  constructor(
    private route: ActivatedRoute,
    private authService : AuthService,
    private router: Router,
    private formBuilder: FormBuilder,
    private alertCtrl: AlertController,
    private geolocation: Geolocation,
  ) { 

  }

  
  ngOnInit() {
    if (this.route && this.route.data) {
      this.getData();
    }
    this.userwho = this.authService.getUserData().uid;

    this.validations_form = this.formBuilder.group({
      event_location: new FormControl('', Validators.compose([
        // Validators.required
      ])),
      event_description: new FormControl('', Validators.compose([
        Validators.required
      ])),
    });


  }

  ngAfterViewInit(){
    this.loadMap();
  }

  setLat(){
    console.log("changed")
    }

 async loadMap() {
    this.geolocation.getCurrentPosition().then((resp) => {

      this.myLatutide = resp.coords.latitude;
      this.mark_lat = resp.coords.latitude;
      this.myLongitude = resp.coords.longitude;
      this.mark_lng = resp.coords.longitude;
      this.myLocation = new google.maps.LatLng(this.myLatutide, this.myLongitude);

      let myOptions = {
        zoom: 15,
        center: this.myLocation,
        mapTypeId: google.maps.MapTypeId.ROADMAP
      };
      
      this.map = new google.maps.Map(this.mapElement.nativeElement, myOptions);

      this.marker = new google.maps.Marker({
          position: this.myLocation,
          map: this.map,
          draggable: true
      });

      this.marker.setMap(this.map);
      
      google.maps.event.addListener(this.map, 'click',(evt)=> {

        this.marker.setPosition(new google.maps.LatLng(evt.latLng.lat().toFixed(5),evt.latLng.lng().toFixed(5)))
        this.changeposition(evt.latLng.lat().toFixed(5),evt.latLng.lng().toFixed(5));

      })

      google.maps.event.addListener(this.marker,'dragend',(evt)=>{
        console.log("marker dropped, lat:"+evt.latLng.lat()+" lng:"+evt.latLng.lng() );
        this.changeposition(evt.latLng.lat().toFixed(5),evt.latLng.lng().toFixed(5));
      })
      google.maps.event.addListener(this.marker,'dragstart',function(evt){
        console.log("currently dragging marker")
      })

    }).catch((error) => {
      console.log('Error getting location', error);
    });
  }
  

  getData(){
    this.route.data.subscribe(routeData => {
     let data = routeData['data'];
     if (data) {
       this.item = data;
     }
    })
  }


  async tryReport(value){
    let report_data = {
      reporter_name : this.item.Name,
      reporter_id : this.item.uid,
      reporter_email : this.item.Email,
      reporter_phone : this.item.Phone,
      event_location : value.event_location,
      event_description : value.event_description,
      lat : this.mark_lat,
      lng : this.mark_lng,
    }
    const alert = await this.alertCtrl.create({
      header: 'Confirm',
      message: '確認報案?',
      buttons: [
        {
          text: 'No',
          role: 'cancel',
          cssClass: 'secondary',
          handler: () => {}
        },
        {
          text: 'Yes',
          handler: () => {
            this.authService.doReport(report_data)
            .then((res)=> {
                this.router.navigate(["/main"]);
              },
              err => console.log(err)
            )
          }
        }
      ]
    });
    await alert.present();
  }

  changeposition(lat,lng){
    this.mark_lat = lat;
    this.mark_lng = lng;
  }

  logout(){
    this.authService.doLogout();
  }


}

