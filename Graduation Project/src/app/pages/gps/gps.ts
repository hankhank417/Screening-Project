// GOOGLE MAP
import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Geolocation } from '@ionic-native/geolocation/ngx';
import { NavController, AlertController } from '@ionic/angular';

import { ConferenceData } from '../../providers/conference-data';
import { ActivatedRoute, Router } from '@angular/router';
import { Http, Response, Headers, RequestOptions } from '@angular/http';
import { LocalNotifications } from '@ionic-native/local-notifications';
import { AuthService } from '../../auth.service';




declare var google;
var map;
var myMarker;
var status: string = "您目前處於安全狀態";

@Component({
  selector: 'page-gps',
  templateUrl: 'gps.html',
  styleUrls: ['./gps.scss'],
})
export class GpsPage implements AfterViewInit{
  @ViewChild('map') mapElement: ElementRef;
  myLongitude: any;
  myLatutide: any;
  myLocation: any;
  myMarker: any;
  accident_icon: any;
  items: Array<any>;
  address: any;

  private apiUrl ='http://140.117.71.131:8080/predict';

  constructor(
    public confData: ConferenceData,
    private route: ActivatedRoute,
    public navCtrl: NavController,
    private geolocation: Geolocation,
    public http: Http,
    private alertCtrl: AlertController,
    private authService : AuthService,
    private router: Router
  ) {
  }

  async ngAfterViewInit() {
    this.loadMap();
    this.addAccidentPoint();
  }

  getAddress(place: Object) {
    this.address = place['formatted_address'];
    console.log('Address Object', place);
  }
  
  loadMap() {

    this.geolocation.getCurrentPosition().then((resp) => {

      this.accident_icon = 'assets/img/accident_icon.png';

      this.myLatutide = resp.coords.latitude;
      this.myLongitude = resp.coords.longitude;
      this.myLocation = new google.maps.LatLng(this.myLatutide, this.myLongitude);

      var directionsDisplay = new google.maps.DirectionsRenderer;

      map = new google.maps.Map(document.getElementById('map'), {
        zoom: 15,
        center: {lat: this.myLatutide, lng: this.myLongitude}
      });

      directionsDisplay.setMap(map);

      const infoWindow = new google.maps.InfoWindow({
        content: '您的位置',
      });

      myMarker = new google.maps.Marker(
        {
          position:this.myLocation,
          title:"您的位置"
        }
      );

      myMarker.setMap(map);

      myMarker.addListener('click', () => {
        infoWindow.open(map, myMarker);
      });

    }).catch((error) => {
      console.log('Error getting location', error);
    });
  }

  addAccidentPoint() {

    this.accident_icon = 'assets/img/accident_icon.png';

    this.route.data.subscribe(routeData => {
      routeData['data'].subscribe(data => {
        data.forEach((item:any)=>{
          var infoWindowContent = `<p style='font-weight:bold; font-size:12pt;'>${item.payload.doc.data().Report_Time}</p>
                                    <p>報案人 : ${item.payload.doc.data().Reporter_Name}</p>
                                    <p>描述 : ${item.payload.doc.data().Event_description}</p>`;

          const infoWindow = new google.maps.InfoWindow({
            content: infoWindowContent
          });

          const marker = new google.maps.Marker({
            position: new google.maps.LatLng(item.payload.doc.data().lat,item.payload.doc.data().lng),
            map: map,
            title: item.payload.doc.data().Report_Time,
            icon: this.accident_icon
          });

          marker.addListener('click', () => {
            infoWindow.open(map, marker);
          });
        })
      })
    })

  }

  calculateAndDisplayRoute() {
    var directionsService = new google.maps.DirectionsService;

    directionsService.route({
      origin: this.myLocation,
      destination: this.address,
      // DRIVING BICYCLING WALKING 
      travelMode: 'DRIVING',
      // 路線選擇
      provideRouteAlternatives: true,
      // 高速公路
      avoidHighways: false,
      // 收費站
      avoidTolls: false
    }, function(response, status) {
      if (status === 'OK') {
        for (var i = 0; i < response.routes.length; i++) {
          var dr = new google.maps.DirectionsRenderer();
          dr.setDirections(response);
          dr.setRouteIndex(i);
          dr.setMap(map);
        }
        myMarker.setMap(null);
      } else {
        window.alert('Directions request failed due to ' + status);
      }
    });
  }

  setLocation() {
    this.geolocation.getCurrentPosition().then((resp) => {
      this.myLatutide = resp.coords.latitude;
      this.myLongitude = resp.coords.longitude;
      this.myLocation = new google.maps.LatLng(this.myLatutide, this.myLongitude);
    }).catch((error) => {
      console.log('Error getting location', error);
    });
  }

  judgingSafety(){

  }

  async postUrlReturn() {
    var headers = new Headers();
    headers.append("Accept", 'application/json, text/plain');
    headers.append('Content-Type', 'application/json' );
    const requestOptions = new RequestOptions({ headers: headers });

    let data = {
      'Longitude':this.myLongitude,
      'Latitude':this.myLatutide
    }

    this.http.post(this.apiUrl, data, requestOptions)
      .subscribe(data => {
        console.log(data['_body']);
        if(data['_body'] == 2){
          status = "您目前處於安全狀態";
        }else{
          status = "危險駕駛! 請減速慢行";
        }
      }, error => {
        console.log(error);
      });

      const alert = await this.alertCtrl.create({
        // header: '',
        message: status,
        buttons: [
          {
            text: 'Yes',
            handler: () => {
              this.router.navigate(["/gps"]);
            }
          }
        ]
      });
      await alert.present();
  }


} //end class

// import requests
// import pandas as pd
// url = 'http://140.117.71.131:8080/predict'
// data = {'Longitude':120.311046,'Latitude':22.611889,'StnPres':1017.1,'Temperature':22.3,'RH':69,'WS':2.0,'WD':330.0,'Precp':0.0,'Y':2013,'M':2,'D':11,'H':18}
// # data = [120.311046,22.611889,1017.1,22.3,69,2.0,330,0.0,2013,2,11,18]
// response = requests.post(url, data=data)
// response.json()