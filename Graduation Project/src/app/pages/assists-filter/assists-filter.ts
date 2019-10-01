import { AfterViewInit, Component } from '@angular/core';
import { Config, ModalController, NavParams, AlertController } from '@ionic/angular';
import { ActivatedRoute } from '@angular/router';

import { ConferenceData } from '../../providers/conference-data';

@Component({
  selector: 'page-assists-filter',
  templateUrl: 'assists-filter.html',
  styleUrls: ['./assists-filter.scss']
})

  



export class AssistsFilterPage implements AfterViewInit {
  ios: boolean;

  tracks: {name: string, icon: string, isChecked: boolean}[] = [];
  items: { title: string; value: string; }[];
  alertController: any;
  itemclass: any;
  http: any;
  showToast: any;
  getClassMessage: any;
  create: any;
  itemAssists: any;

  constructor(
    public confData: ConferenceData,
    private config: Config,
    public modalCtrl: ModalController,
    public navParams: NavParams,
    public alertCtrl: AlertController,
    private route: ActivatedRoute
  ) { 
    this.items = [
      // {title: '醫院'},
      // {title: '修車廠'},
      // {title: '派出所'}
      {
        "title": "醫院",
        "value": "hospital"
      },
      {
        "title": "修車廠",
        "value": "school"
      },
      {
        "title": "派出所",
        "value": "station"
      },
    ];
  }

  ionViewWillEnter() {
    this.ios = this.config.get('mode') === `ios`;
  }

  // TODO use the ionViewDidEnter event
  ngAfterViewInit() {
    // passed in array of track names that should be excluded (unchecked)
    const excludedTrackNames = this.navParams.get('excludedTracks');

    this.confData.getTracks().subscribe((tracks: any[]) => {
      tracks.forEach(track => {
        this.tracks.push({
          name: track.name,
          icon: track.icon,
          isChecked: (excludedTrackNames.indexOf(track.name) === -1)
        });
      });
    });
  }

  selectAll(check: boolean) {
    // set all to checked or unchecked
    this.tracks.forEach(track => {
      track.isChecked = check;
    });
  }

  applyFilters() {
    // Pass back a new array of track names to exclude
    const excludedTrackNames = this.tracks.filter(c => !c.isChecked).map(c => c.name);
    this.dismiss(excludedTrackNames);
  }

  dismiss(data?: any) {
    // using the injected ModalController this page
    // can "dismiss" itself and pass back data
    this.modalCtrl.dismiss(data);
  }

  async removeItem(item: { title: string; }){
 
    for(var i = 0; i < this.items.length; i++) {
 
      if(this.items[i] == item){
        this.items.splice(i, 1);
      }
 
    }
    const alert = await this.alertCtrl.create({
      header: 'Location Deleted',
      buttons: [{
        text: 'OK',
        handler: () => {
          // close the sliding item
          close();
        }
      }]
    });
 
  }


  // addItem(itemclass: any, node: any) {
  //   node.close();
  //   this.itemclass = itemclass;
  //   this.addWindow();
  // }


  async addItem(){
    const alert = await this.alertCtrl.create({
      header: '新增支援地點',
      inputs: [
        {
          name: 'itemName',
          type: 'text',
          placeholder: '新增支援地點名稱',
          value: this.itemAssists
        }
      ],
      buttons: [
        {
          text: '取消',
          role: 'cancel',
          handler: () => {
            return;
          }
        },
        {
          text: '確定',
          handler: data =>{
            if(data.itemName.trim === '') {
              this.showToast();
              this.addItem();
            } else {
               this.addOk(data.itemName);
            }
          }
        }
      ]
    });
    await alert.present();
  }

  addOk( itemName: { title: string; value: string;} ) {
    var i = this.items.length
    this.items[i] = itemName
    // const url = "brainstorming-web/class/modify";
    // this.itemclass.theme = itemName;
    // const body = JSON.stringify(this.itemName);
    // this.http.put(url, body).subscribe(
    //   res => {
    //     if (res.json().id !== undefined && res.json().id !== null) {
    //       this.showToast();
    //       this.getClassMessage();
    //     } else {
    //       this.showToast();
    //     }

    //   }
    // );
  }
  // create(_arg0: { header: string; inputs: { name: string; type: string; placeholder: string; value: { title: string; }[]; }[]; buttons: ({ text: string; role: string; handler: () => void; } | { text: string; handler: (data: any) => void; })[]; }) {
  //   throw new Error("Method not implemented.");
  // }
  toastCtrl() {
    throw new Error("Method not implemented.");
  }

  //   await alert.present();
  // }
  // toastCtrl(toastCtrl: any, arg1: string) {
  //   throw new Error("Method not implemented.");
  // }


  // }
  // getClassMessage() {
  //   throw new Error("Method not implemented.");
  // }
}
