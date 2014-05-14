//
//  ofxStreetView.h
//
//  Created by Patricio Gonzalez Vivo on 3/10/14.
//
//  Credits to:
//              Paul Wagener https://github.com/PaulWagener/Streetview-Explorer
//

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

struct DepthMapPlane {
    float x, y, z;
    float d;
};

struct Link {
    float yaw_deg;
    string pano_id;
};

class ofxStreetView : public ofBaseHasTexture {
public:
    
    ofxStreetView();
    ofxStreetView(string _pano_id);
	ofxStreetView(double _lat, double _lng);
    
    virtual     ~ofxStreetView();
    
    void        setPanoId(string _pano_id);
    void        setLatLon(double _lat, double _lng);
    void        setZoom(int _zoom);
    
    void        setUseTexture(bool _bUseTex);
    bool        isTextureLoaded(){return bPanoLoaded;};
    
    float       getWidth();
	float       getHeight();
    
    double      getLat(){return lat;}
    double      getLon(){return lon;}
    float       getDirection(){return pano_yaw_deg;}
    float       getTiltPitch(){return tilt_pitch_deg;}
    float       getTiltYaw(){return tilt_yaw_deg;}
    float       getGroundHeight();
    
    ofTexture&  getTextureReference();
    
    ofTexture   getTextureAt(float _deg, float _amp);
    
    string      getPanoId(){return pano_id;};
    string      getCloseLinkTo(float _deg);
    
    int         getDepthMapWidth(){return mapWidth;}
    int         getDepthMapHeight(){return mapHeight;}
    ofImage     getDepthMap();
    ofVboMesh&  getDethMesh(){return meshDepth;};
    DepthMapPlane getDepthMapAt(int _x, int _y);

    void        urlResponse(ofHttpResponse & response);
    void        clear();
    
    void        update();
    void        draw();
    
    vector<Link> links;
    
protected:
    void        downloadPanorama();
    vector<ofImage> panoImages;
    ofFbo       panoFbo;
    
    void        makeDepthMesh();
    void        addVertex(int x, int y);
    ofVboMesh   meshDepth;
    
    string      data_url;
    string      pano_id;
    float       pano_yaw_deg,tilt_yaw_deg,tilt_pitch_deg;
    int         num_zoom_levels;

    //Depth map information
    vector<unsigned char> depthmapIndices;
    vector<DepthMapPlane> depthmapPlanes;
    int         mapWidth, mapHeight, maxDistance;
    string      depth_map_base64;
    
    //  Location
    double      lat,lon;
    int         zoom;
    
    //  Flags
    //
    bool        bDataLoaded;
    bool        bPanoLoaded;
    
    bool        bRegister;
    bool        bTexture;
};