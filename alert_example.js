// Node-RED pseudocode for alerting
// Subscribe to vehicle/<id>/data, check geofence, send alert
// function node:
// var p = msg.payload;
// var dist = haversine(p.lat, p.lon, GEOFENCE_LAT, GEOFENCE_LON);
// if (dist > GEOFENCE_RADIUS && p.locked) { node.send([msg, null]); } else { node.send([null, msg]); }
