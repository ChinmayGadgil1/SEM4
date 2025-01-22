"use client";
import React, { useState } from 'react';
import { 
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle 
} from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { Button } from "@/components/ui/button";
import { Tabs, TabsList, TabsTrigger, TabsContent } from "@/components/ui/tabs";
import { Progress } from "@/components/ui/progress";
import { 
  BarChart,
  Bar,
  XAxis,
  YAxis,
  CartesianGrid,
  Tooltip,
  ResponsiveContainer
} from 'recharts';
import {
  Search,
  TrendingUp,
  Target,
  FileText,
} from 'lucide-react';

import { FaYoutube,FaReddit,FaQuora } from 'react-icons/fa';

const ARTFinderDashboard = () => {
  const [searchTerm, setSearchTerm] = useState('');
  const [brandGuidelines, setBrandGuidelines] = useState('');
  
  // Sample data - replace with real data
  const sentimentData = [
    { name: 'Positive', value: 65 },
    { name: 'Neutral', value: 20 },
    { name: 'Negative', value: 15 }
  ];

  const painPoints = [
    { issue: 'Time Management', frequency: 78 },
    { issue: 'Cost Concerns', frequency: 65 },
    { issue: 'Technical Difficulty', frequency: 45 },
    { issue: 'Integration Problems', frequency: 32 }
  ];

  return (
    <div className="min-h-screen bg-gray-900 text-white p-6">
      {/* Header Section */}
      <div className="mb-8">
        <h1 className="text-3xl font-bold mb-2">ART Finder Dashboard</h1>
        <p className="text-white">Automated Research and Trigger Finder</p>
      </div>

      {/* Search Section */}
      <div className="grid grid-cols-1 md:grid-cols-2 gap-4 mb-8">
        <div className="space-y-4">
          <Input
            placeholder="Enter research topic..."
            value={searchTerm}
            onChange={(e) => setSearchTerm(e.target.value)}
            className="bg-gray-800 border-gray-700"
          />
          <Input
            placeholder="Enter brand guidelines..."
            value={brandGuidelines}
            onChange={(e) => setBrandGuidelines(e.target.value)}
            className="bg-gray-800 border-gray-700"
          />
        </div>
        <div className="flex items-end">
          <Button className="w-full md:w-auto bg-blue-600 hover:bg-blue-700">
            <Search className="mr-2 h-4 w-4" />
            Start Research
          </Button>
        </div>
      </div>

      {/* Main Content */}
      <Tabs defaultValue="insights" className="space-y-4">
        <TabsList className="bg-gray-800">
          <TabsTrigger value="insights" className="data-[state=active]:bg-gray-200">
            <TrendingUp className="mr-2 h-4 w-4" />
            Insights
          </TabsTrigger>
          <TabsTrigger value="competitors" className="data-[state=active]:bg-gray-200">
            <Target className="mr-2 h-4 w-4" />
            Competitors
          </TabsTrigger>
          <TabsTrigger value="content" className="data-[state=active]:bg-gray-200">
            <FileText className="mr-2 h-4 w-4" />
            Content
          </TabsTrigger>
        </TabsList>

        <TabsContent value="insights" className="space-y-4">
          <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
            {/* Sentiment Analysis Card */}
            <Card className="bg-gray-800 border-gray-700">
              <CardHeader>
                <CardTitle className='text-gray-50 font-extrabold'>Sentiment Analysis</CardTitle>
                <CardDescription className="text-white">Overall user sentiment</CardDescription>
              </CardHeader>
              <CardContent>
                <div className="h-64">
                  <ResponsiveContainer width="100%" height="100%">
                    <BarChart data={sentimentData}>
                      <CartesianGrid strokeDasharray="3 3" stroke="#374151" />
                      <XAxis dataKey="name" stroke="#9CA3AF" />
                      <YAxis stroke="#9CA3AF" />
                      <Tooltip 
                        contentStyle={{ backgroundColor: '#1F2937', border: 'none' }}
                        labelStyle={{ color: '#F9FAFB' }}
                      />
                      <Bar dataKey="value" fill="#3B82F6" />
                    </BarChart>
                  </ResponsiveContainer>
                </div>
              </CardContent>
            </Card>

            {/* Pain Points Card */}
            <Card className="bg-gray-800 border-gray-700">
              <CardHeader>
                <CardTitle className='text-gray-50 font-extrabold'>Top Pain Points</CardTitle>
                <CardDescription className="text-white">User-reported issues</CardDescription>
              </CardHeader>
              <CardContent>
                <div className="space-y-4 text-gray-100">
                  {painPoints.map((point, index) => (
                    <div key={index}>
                      <div className="flex justify-between mb-1">
                      <span className="text-sm">{point.issue}</span>
                      <span className="text-sm text-white">{point.frequency}%</span>
                      </div>
                      <Progress value={point.frequency} className="h-2 border border-violet-500" />
                      
                    </div>
                  ))}
                </div>
              </CardContent>
            </Card>

            {/* Source Distribution Card */}
            <Card className="bg-gray-800 border-gray-700">
              <CardHeader>
                <CardTitle className='text-gray-50 font-extrabold'>Data Sources</CardTitle>
                <CardDescription className="text-white">Content distribution</CardDescription>
              </CardHeader>
              <CardContent>
                <div className="space-y-4">
                  <div className="flex items-center justify-between">
                    <div className="flex items-center ">
                      <FaYoutube className="mr-2 h-4 w-4 text-[#FF0000]" />
                      <span className='text-white'>YouTube</span>
                    </div>
                    <span className='text-white'>45%</span>
                  </div>
                  <div className="flex items-center justify-between">
                    <div className="flex items-center">
                      <FaReddit className="mr-2 h-4 w-4 text-[#FF5700]" />
                      <span className='text-white'>Reddit</span>
                    </div>
                    <span  className='text-white'>30%</span>
                  </div>
                  <div className="flex items-center justify-between">
                    <div className="flex items-center">
                      <FaQuora className="mr-2 h-4 w-4 text-[#a62100]" />
                      <span className='text-white'>Quora</span>
                    </div>
                    <span  className='text-white'>25%</span>
                  </div>
                </div>
              </CardContent>
            </Card>
          </div>
        </TabsContent>

        <TabsContent value="competitors" className="space-y-4">
          <Card className="bg-gray-800 border-gray-700">
            <CardHeader>
              <CardTitle className='text-gray-50 font-extrabold'>Competitor Analysis</CardTitle>
              <CardDescription className="text-white">Coming soon...</CardDescription>
            </CardHeader>
          </Card>
        </TabsContent>

        <TabsContent value="content" className="space-y-4">
          <Card className="bg-gray-800 border-gray-700">
            <CardHeader>
              <CardTitle className='text-gray-50 font-extrabold'>Content Analysis</CardTitle>
              <CardDescription className="text-white">Coming soon...</CardDescription>
            </CardHeader>
          </Card>
        </TabsContent>
      </Tabs>
    </div>
  );
};

export default ARTFinderDashboard;