import { CUSTOM_ELEMENTS_SCHEMA } from '@angular/core';
import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { Privacy2Page } from './privacy2.page';

describe('Privacy2Page', () => {
  let component: Privacy2Page;
  let fixture: ComponentFixture<Privacy2Page>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ Privacy2Page ],
      schemas: [CUSTOM_ELEMENTS_SCHEMA],
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(Privacy2Page);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
