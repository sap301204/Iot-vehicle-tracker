# Cloud Database & Analytics

Options:
1) InfluxDB + Grafana
   - Use Node-RED 'influxdb out' node to write telemetry points to InfluxDB.
   - Schema: measurement = vehicle_telemetry, fields = lat, lon, speed, locked, tags = vehicle_id
   - Visualize in Grafana: speed over time, route history via worldmap panel or export to GeoJSON for Google Maps.

2) Firebase (Realtime DB or Firestore)
   - Use Node-RED 'http request' or firebase nodes to push JSON messages under /vehicles/<id>/logs.
   - Use Google Maps API or custom web app to render polylines from stored points.

Google Maps API:
- Retrieve stored coordinates, form polyline, display on map using Maps JavaScript API.

Sample InfluxDB write (Node-RED):
- measurement: vehicle_telemetry
- tags: vehicle_id=vehicle001
- fields: lat=12.97, lon=77.59, speed=12.3, locked=true
